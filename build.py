import os
from shutil import rmtree
import subprocess
import glob
from pathlib import Path

supportedExtensions = [".c", ".asm", ".s"]
linkerScriptName = "linker.ld"

filesToCompile = []

if (os.path.exists("bin/iso")):
    rmtree("bin/iso")

for ext in supportedExtensions:
    for file in glob.glob(os.getcwd() + '/**/*' + ext, recursive=True):
        if not os.path.exists("bin"):
            os.mkdir("bin")
            os.mkdir("bin/obj")
            os.mkdir("bin/iso")
            os.mkdir("bin/iso/boot")
        match ext:
            case ".c":
                subprocess.run(["x86_64-elf-gcc", "-o", file.split(".")[0].split(os.getcwd() + "/")[1] + ".o", Path.resolve(Path(file.split(".")[0].split(os.getcwd() + "/")[1] + ext)), "-Wall", "-Wextra", "-std=gnu11", "-ffreestanding", "-fno-stack-protector",
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
                                "-mno-red-zone"])
            case ".asm" | ".s":
                subprocess.run(["nasm", "-Wall", "-felf64", "-o", file.split(".")[0].split(os.getcwd() + "/")[1] + ".o"])
        filesToCompile.append(file.split(".")[0].split(os.getcwd() + "/")[1] + ".o")
        
subprocess.run(["ld", "-o", "bin/iso/AtomOS.elf", "bin/obj/" + (" bin/obj/".join(filesToCompile)), "-m", "elf_x86_64", "-nostdlib", "-static", "-pie",
                "--no-dynamic-linker", "-ztext", "-zmax-page-size=0x1000", "-T", linkerScriptName])

if (os.path.exists("bin/iso")):
    cfgContents = open("temp/limine.cfg")
    copiedFile = open("bin/iso/limine.cfg", "x")
    copiedFile.write(cfgContents.read())

    cfgContents.close()
    copiedFile.close()

    subprocess.run(["cp", "-v", "limine/limine-bios.sys", "limine/limine-bios-cd.bin", "limine/limine-uefi-cd.bin", "bin/iso/"])

    os.mkdir("bin/iso/EFI/BOOT")
    subprocess.run(["cp", "-v", "limine/BOOTX64.EFI", "bin/iso/EFI/BOOT/"])
    subprocess.run(["cp", "-v", "limine/BOOTIA32.EFI", "bin/iso/EFI/BOOT/"])

    subprocess.run(["xorriso", "-as", "mkisofs", "-b", "limine-bios-cd.bin","-no-emul-boot", "-boot-load-size", "4", "-boot-info-table", 
                    "--efi-boot", 
                    "limine-uefi-cd.bin",
                    "-efi-boot-part", 
                    "--efi-boot-image", 
                    "--protective-msdos-label", 
                    "bin/iso", 
                    "-o", 
                    "bin/iso/AtomOS.iso"])
    subprocess.run(["sudo", "./limine/limine bios-install", "bin/iso/AtomOS.iso"])