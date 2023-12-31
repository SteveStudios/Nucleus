![logo](https://github.com/SteveStudios/Nucleus/assets/90519370/d19139d5-efc6-45e8-b7fe-a90063f319f8)

# Nucleus

Nucleus is a hybrid operating system kernel designed to run on the x86_64/amd64 architecture. It has been developed in small steps since July of 2023.

Nucleus is the biggest component of a much bigger project called Atom OS, which is an attempt at making a full, modern, and stable operating system from scratch that can be bundled with the upcoming Atom computers - which have already been fully planned out.

# Building Nucleus

## Prequisites

- `x86_64-elf-gcc`
- `x86_64-elf-ld`
- `nasm`
- `xorriso`
- `qemu`
- `python3`

You will also need A UNIX utility set, such as GNU coreutils (This is only required if you are using a non UNIX-like Host, i.e; If you are running OS X or GNU/Linux, you do not need to do this step).

# Obtaining Limine

## Prequisites

- `make`
  
Limine is the bootloader of choice for Nucleus. To obtain Limine, simply "cd" into the "lib" folder and run the following commands:

```
git clone https://github.com/limine-bootloader/limine.git --branch=v5.x-branch-binary --depth=1
make -C limine
```

# Nucleus Build Script

Nucleus does not use Makefiles, instead it uses a python script called "build.py" to build the kernel.
You need to run this script as root to build Nucleus, e.g: "sudo python3 build.py".

Assuming you have all the dependencies installed, Nucleus should build and place a raw binary, an ISO image (Which you need to boot Nucleus), and some other files into a directory called "bin".
