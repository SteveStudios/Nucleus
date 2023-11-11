# build.py - Atom OS Build Script
# Created 2023/7/10 by Stephen Byrne

import os
import platform
from shutil import rmtree
import subprocess
import glob

supportedExtensions = [".c", ".asm", ".s"]
linkerScriptName = "link.ld"

filesToCompile = []

if (os.path.exists("bin/iso")):
    rmtree("bin/iso")
if (not os.path.exists("bin")):
    os.mkdir("bin")
if (not os.path.exists("bin/obj")):
    os.mkdir("bin/obj")
if (not os.path.exists("bin/iso")):
    os.mkdir("bin/iso")
if (not os.path.exists("bin/iso/EFI")):
    os.mkdir("bin/iso/EFI")
if (not os.path.exists("bin/iso/EFI/BOOT")):
    os.mkdir("bin/iso/EFI/BOOT")

for ext in supportedExtensions:
    for file in glob.iglob('**/*' + ext, recursive=True):
        if (not ("." + file.split(".")[1]) in supportedExtensions): continue
        if os.path.isdir(file) or file.endswith("/limine.c"): continue
        match ext:
            case ".c":
                subprocess.run(["x86_64-elf-gcc", "-std=gnu11", "-ffreestanding", "-fno-stack-protector",
                                "-fno-stack-check",
                                "-fno-lto",
                                "-fPIE",
                                "-m64",
                                "-march=x86-64",
                                "-mabi=sysv",
                                "-mno-80387",
                                "-mno-mmx",
                                "-mno-sse",
                                "-mno-sse2",
                                "-mno-red-zone", "-c", file, "-o", "bin/obj/" + file.split("/")[len(file.split(".")[0].split("/")) - 1].split(".")[0] + ".o"])
            case ".asm" | ".s":
                subprocess.run(["nasm", "-Wall", "-felf64", "-o", "bin/obj/" + file.split("/")[len(file.split(".")[0].split("/")) - 1].split(".")[0] + ".o", file])
        filesToCompile.append(file.split("/")[len(file.split("/")) - 1].split(".")[0] + ".o")

argArr = ["x86_64-elf-ld", "-o", "bin/iso/AtomOS.elf"]

for file in filesToCompile:
    argArr.append("bin/obj/" + file)
for endingArg in ["-m", "elf_x86_64", "-nostdlib", "-static", "-pie", "--no-dynamic-linker", "-ztext", "-T", linkerScriptName]:
    argArr.append(endingArg)

subprocess.run(argArr)

if (os.path.exists("bin/iso")):
    cfgContents = open("rootfs/limine.cfg")
    copiedFile = open("bin/iso/limine.cfg", "x")
    copiedFile.write(cfgContents.read())

    cfgContents.close()
    copiedFile.close()

    subprocess.run(["cp", "-v", "lib/limine/limine-bios.sys", "lib/limine/limine-bios-cd.bin", "lib/limine/limine-uefi-cd.bin", "bin/iso/"])

    subprocess.run(["cp", "-v", "lib/limine/BOOTX64.EFI", "bin/iso/EFI/BOOT/"])
    subprocess.run(["cp", "-v", "lib/limine/BOOTIA32.EFI", "bin/iso/EFI/BOOT/"])

    subprocess.run(["xorriso", "-as", "mkisofs", "-b", "limine-bios-cd.bin","-no-emul-boot", "-boot-load-size", "4", "-boot-info-table", 
                    "--efi-boot", 
                    "limine-uefi-cd.bin",
                    "-efi-boot-part", 
                    "--efi-boot-image", 
                    "--protective-msdos-label", 
                    "bin/iso", 
                    "-o", 
                    "bin/iso/AtomOS.iso"])
    
    if platform.system() == "Windows":
        subprocess.run(["lib/limine/limine.exe", "bios-install", "bin/iso/AtomOS.iso"])
    elif platform.system() == "Darwin":
        subprocess.run([os.getcwd() + "/lib/limine/limine", "bios-install", "bin/iso/AtomOS.iso"])
    elif platform.system() == "Linux":
        subprocess.run(["./lib/limine/limine", "bios-install", "bin/iso/AtomOS.iso"])

useQemu = input("Would you like to run QEMU? (Y/n): ")
if (useQemu.replace(" ", "") != "y" and useQemu.replace(" ", "") != "n" and useQemu.replace(" ", "") != ""):
    print("Error: Unknown response")

match useQemu.replace(" ", ""):
    case "y":
        subprocess.run(["qemu-system-x86_64", "-boot", "d", "-cdrom", 'bin/iso/AtomOS.iso', "-d", "int", "-m", "2048", "-M", "smm=off"])
    case "":
        subprocess.run(["qemu-system-x86_64", "-boot", "d", "-cdrom", 'bin/iso/AtomOS.iso', "-d", "int", "-m", "2048", "-M", "smm=off"])
    case "n":
        exit(0)