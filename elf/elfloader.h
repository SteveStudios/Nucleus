// elf_loader.h - ELF program loader
// Created 2023/11/09 by Stephen Byrne

#pragma once

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <stdbool.h>
#include "../kernel_lib/io.h"
#include "../lib/liballoc/liballoc.h"
#include "../kernel_lib/mem.h"

	typedef uint64_t Elf64_Half;
	typedef uint64_t Elf64_Off;
	typedef uint64_t Elf64_Addr;
	typedef uint64_t Elf64_Word;
	typedef int64_t Elf64_Sword;
	typedef uint64_t Elf64_Xword;
	typedef int64_t Elf64_Sxword;
	typedef uint64_t Elf64_Off;

	typedef struct
	{
		Elf64_Word p_type;
		Elf64_Word p_flags;
		Elf64_Off p_offset;
		Elf64_Addr p_vaddr;
		Elf64_Addr p_paddr;
		Elf64_Xword p_filesz;
		Elf64_Xword p_memsz;
		Elf64_Xword p_align;
	} Elf64_Phdr;

	enum Elf_Ident
	{
		EI_MAG0 = 0,
		EI_MAG1 = 1,
		EI_MAG2 = 2,
		EI_MAG3 = 3,
		EI_CLASS = 4,
		EI_DATA = 5,
		EI_VERSION = 6,
		EI_OSABI = 7,
		EI_ABIVERSION = 8,
		EI_PAD = 9
	};

#define ELFMAG0 0x7F // e_ident[EI_MAG0]
#define ELFMAG1 'E'	 // e_ident[EI_MAG1]
#define ELFMAG2 'L'	 // e_ident[EI_MAG2]
#define ELFMAG3 'F'	 // e_ident[EI_MAG3]

#define ELFDATA2LSB (1) // Little Endian
#define ELFCLASS64 (1)	// 64-bit Architecture

#define EI_NIDENT 16

	enum Elf_Type
	{
		ET_NONE = 0, // Unkown
		ET_REL = 1,	 // Relocatable
		ET_EXEC = 2	 // Executable
	};

#define EM_X86_64 (62) // x86_64 Machine Type
#define EV_CURRENT (1) // ELF Current Version

	typedef struct
	{
		unsigned char e_ident[EI_NIDENT];
		Elf64_Half e_type;
		Elf64_Half e_machine;
		Elf64_Word e_version;
		Elf64_Addr e_entry;
		Elf64_Off e_phoff;
		Elf64_Off e_shoff;
		Elf64_Word e_flags;
		Elf64_Half e_ehsize;
		Elf64_Half e_phentsize;
		Elf64_Half e_phnum;
		Elf64_Half e_shentsize;
		Elf64_Half e_shnum;
		Elf64_Half e_shstrndx;
	} Elf64_Ehdr;

#define SHN_UNDEF (0x00)

	typedef struct
	{
		Elf64_Word sh_name;
		Elf64_Word sh_type;
		Elf64_Word sh_flags;
		Elf64_Addr sh_addr;
		Elf64_Off sh_offset;
		Elf64_Word sh_size;
		Elf64_Word sh_link;
		Elf64_Word sh_info;
		Elf64_Word sh_addralign;
		Elf64_Word sh_entsize;
	} Elf64_Shdr;

	enum ShT_Types
	{
		SHT_NULL = 0,
		SHT_PROGBITS = 1,
		SHT_SYMTAB = 2,
		SHT_STRTAB = 3,
		SHT_RELA = 4,
		SHT_NOBITS = 8,
		SHT_REL = 9,
	};

	enum ShT_Attributes
	{
		SHF_WRITE = 0x01,
		SHF_ALLOC = 0x02 
	};

	typedef struct
	{
		Elf64_Word st_name;
		Elf64_Addr st_value;
		Elf64_Word st_size;
		uint16_t st_info;
		uint16_t st_other;
		Elf64_Half st_shndx;
	} Elf64_Sym;

#define ELF64_ST_BIND(INFO) ((INFO) >> 4)
#define ELF64_ST_TYPE(INFO) ((INFO)&0x0F)

	enum StT_Bindings
	{
		STB_LOCAL = 0,
		STB_GLOBAL = 1,
		STB_WEAK = 2
	};

	enum StT_Types
	{
		STT_NOTYPE = 0,
		STT_OBJECT = 1,
		STT_FUNC = 2
	};

	typedef struct
	{
		Elf64_Addr r_offset;
		Elf64_Word r_info;
	} Elf64_Rel;

	typedef struct
	{
		Elf64_Addr r_offset;
		Elf64_Word r_info;
		Elf64_Sword r_addend;
	} Elf64_Rela;

#define ELF64_R_SYM(INFO) ((INFO) >> 8)
#define ELF64_R_TYPE(INFO) ((uint8_t)(INFO))

#define ELF_RELOC_ERR -1

	enum RtT_Types
	{
		R_X86_64_NONE = 0,
		R_X86_64_64 = 1,
		R_X86_64_PC64 = 2
	};

#ifdef __cplusplus
}
#endif