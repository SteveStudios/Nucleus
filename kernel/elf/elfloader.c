// elf_loader.c - ELF program loader
// Created 2023/11/09 by Stephen Byrne

#include "elfloader.h"

bool elf_check_file(Elf64_Ehdr *hdr)
{
    if (!hdr)
        return false;
    if (hdr->e_ident[EI_MAG0] != ELFMAG0)
    {
        println("[ERROR] ELF Header EI_MAG0 incorrect.\n");
        return false;
    }
    if (hdr->e_ident[EI_MAG1] != ELFMAG1)
    {
        println("[ERROR] ELF Header EI_MAG1 incorrect.\n");
        return false;
    }
    if (hdr->e_ident[EI_MAG2] != ELFMAG2)
    {
        println("[ERROR] ELF Header EI_MAG2 incorrect.\n");
        return false;
    }
    if (hdr->e_ident[EI_MAG3] != ELFMAG3)
    {
        println("[ERROR] ELF Header EI_MAG3 incorrect.\n");
        return false;
    }
    return true;
}

bool elf_check_supported(Elf64_Ehdr *hdr)
{
    if (!elf_check_file(hdr))
    {
        println("[ERROR] Invalid ELF File.\n");
        return false;
    }
    if (hdr->e_ident[EI_CLASS] != ELFCLASS64)
    {
        println("[ERROR] Unsupported ELF File Class.\n");
        return false;
    }
    if (hdr->e_ident[EI_DATA] != ELFDATA2LSB)
    {
        println("[ERROR] Unsupported ELF File byte order.\n");
        return false;
    }
    if (hdr->e_machine != EM_X86_64)
    {
        println("[ERROR] Unsupported ELF File target.\n");
        return false;
    }
    if (hdr->e_ident[EI_VERSION] != EV_CURRENT)
    {
        println("[ERROR] Unsupported ELF File version.\n");
        return false;
    }
    if (hdr->e_type != ET_REL && hdr->e_type != ET_EXEC)
    {
        println("[ERROR] Unsupported ELF File type.\n");
        return false;
    }
    return true;
}

Elf64_Shdr *elf_sheader(Elf64_Ehdr *hdr)
{
    return (Elf64_Shdr *)((int)hdr + hdr->e_shoff);
}

Elf64_Shdr *elf_section(Elf64_Ehdr *hdr, int idx)
{
    return &elf_sheader(hdr)[idx];
}

int elf_load_stage1(Elf64_Ehdr *hdr)
{
    Elf64_Shdr *shdr = elf_sheader(hdr);

    unsigned int i;
    for (i = 0; i < hdr->e_shnum; i++)
    {
        Elf64_Shdr *section = &shdr[i];
        if (section->sh_type == SHT_NOBITS)
        {

            if (!section->sh_size)
                continue;
            if (section->sh_flags & SHF_ALLOC)
            {
                void *mem = malloc(section->sh_size);
                memset(mem, 0, section->sh_size);
                section->sh_offset = (int)mem - (int)hdr;
            }
        }
    }
    return 0;
}

int elf_load_stage2(Elf64_Ehdr *hdr)
{
    Elf64_Shdr *shdr = elf_sheader(hdr);

    unsigned int i, idx;
    for (i = 0; i < hdr->e_shnum; i++)
    {
        Elf64_Shdr *section = &shdr[i];
        if (section->sh_type == SHT_REL)
        {
            for (idx = 0; idx < section->sh_size / section->sh_entsize; idx++)
            {
                Elf64_Rel *reltab = &((Elf64_Rel *)((int)hdr + section->sh_offset))[idx];
                int result = elf_do_reloc(hdr, reltab, section);
                if (result == ELF_RELOC_ERR)
                {
                    println("[ERROR] Failed to relocate symbol");
                    return ELF_RELOC_ERR;
                }
            }
        }
    }
    return 0;
}

void *elf_load_rel(Elf64_Ehdr *hdr)
{
    int result;
    result = elf_load_stage1(hdr);
    if (result == ELF_RELOC_ERR)
    {
        println("[ERROR] Unable to load ELF file.\n");
        return NULL;
    }
    result = elf_load_stage2(hdr);
    if (result == ELF_RELOC_ERR)
    {
        println("[ERROR] Unable to load ELF file.\n");
        return NULL;
    }
    return (void *)hdr->e_entry;
}

void *elf_load_file(void *file)
{
    Elf64_Ehdr *hdr = (Elf64_Ehdr *)file;
    if (!elf_check_supported(hdr))
    {
        println("[ERROR] ELF File cannot be loaded.\n");
        return;
    }
    switch (hdr->e_type)
    {
    case ET_EXEC:
        return NULL;
    case ET_REL:
        return elf_load_rel(hdr);
    }
    return NULL;
}

char *elf_str_table(Elf64_Ehdr *hdr)
{
    if (hdr->e_shstrndx == SHN_UNDEF)
        return NULL;
    return (char *)hdr + elf_section(hdr, hdr->e_shstrndx)->sh_offset;
}

char *elf_lookup_string(Elf64_Ehdr *hdr, int offset)
{
    char *strtab = elf_str_table(hdr);
    if (strtab == NULL)
        return NULL;
    return strtab + offset;
}

int elf_get_symval(Elf64_Ehdr *hdr, int table, unsigned int idx)
{
    if (table == SHN_UNDEF || idx == SHN_UNDEF)
        return 0;
    Elf64_Shdr *symtab = elf_section(hdr, table);

    uint64_t symtab_entries = symtab->sh_size / symtab->sh_entsize;
    if (idx >= symtab_entries)
    {
        println("[ERROR] Symbol Index out of Range");
        return ELF_RELOC_ERR;
    }

    int symaddr = (int)hdr + symtab->sh_offset;

    Elf64_Sym *symbol = &((Elf64_Sym *)symaddr)[idx];
    if (symbol->st_shndx == SHN_UNDEF)
    {
        Elf64_Shdr *strtab = elf_section(hdr, symtab->sh_link);
        const char *name = (const char *)hdr + strtab->sh_offset + symbol->st_name;

        void *target = NULL;

        if (target == NULL)
        {
            if (ELF64_ST_BIND(symbol->st_info) & STB_WEAK)
                return 0;
            else
            {
                println("[ERROR] Undefined External Symbol");
                return ELF_RELOC_ERR;
            }
        }
        else
            return (int)target;
    }
}

#define DO_x86_64_64(S, A) ((S) + (A))
#define DO_x86_64_PC64(S, A, P) ((S) + (A) - (P))

int elf_do_reloc(Elf64_Ehdr *hdr, Elf64_Rel *rel, Elf64_Shdr *reltab)
{
    Elf64_Shdr *target = elf_section(hdr, reltab->sh_info);

    int addr = (int)hdr + target->sh_offset;
    int *ref = (int *)(addr + rel->r_offset);

    int symval = 0;
    if (ELF64_R_SYM(rel->r_info) != SHN_UNDEF)
    {
        symval = elf_get_symval(hdr, reltab->sh_link, ELF64_R_SYM(rel->r_info));
        if (symval == ELF_RELOC_ERR)
            return ELF_RELOC_ERR;
    }

    switch (ELF64_R_TYPE(rel->r_info))
    {
    case R_X86_64_NONE:
        break;
    case R_X86_64_64:
        *ref = DO_x86_64_64(symval, *ref);
        break;
    case R_X86_64_PC64:
        *ref = DO_x86_64_PC64(symval, *ref, (int)ref);
        break;
    default:
        println("[ERROR] Unsupported Relocation Type");
        return ELF_RELOC_ERR;
    }
    return symval;
}