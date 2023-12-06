#include <elf.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void display_error_and_exit(const char *error_message) {
    fprintf(stderr, "Error: %s\n", error_message);
    exit(98);
}

void display_elf_header(const char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        display_error_and_exit("Can't read file");
    }

    Elf64_Ehdr header;
    if (read(fd, &header, sizeof(header)) != sizeof(header)) {
        close(fd);
        display_error_and_exit("Unable to read ELF header");
    }

    if (header.e_ident[EI_MAG0] != ELFMAG0 || header.e_ident[EI_MAG1] != ELFMAG1 ||
        header.e_ident[EI_MAG2] != ELFMAG2 || header.e_ident[EI_MAG3] != ELFMAG3) {
        close(fd);
        display_error_and_exit("Not an ELF file");
    }

    printf("ELF Header:\n");
    printf("  Magic:   ");
    for (int i = 0; i < EI_NIDENT; ++i) {
        printf("%02x ", header.e_ident[i]);
    }
    printf("\n");

    printf("  Class:                             ");
    switch (header.e_ident[EI_CLASS]) {
        case ELFCLASSNONE: printf("none\n"); break;
        case ELFCLASS32:   printf("ELF32\n"); break;
        case ELFCLASS64:   printf("ELF64\n"); break;
        default:           printf("<unknown: %x>\n", header.e_ident[EI_CLASS]);
    }

    printf("  Data:                              ");
    switch (header.e_ident[EI_DATA]) {
        case ELFDATANONE: printf("none\n"); break;
        case ELFDATA2LSB: printf("2's complement, little endian\n"); break;
        case ELFDATA2MSB: printf("2's complement, big endian\n"); break;
        default:           printf("<unknown: %x>\n", header.e_ident[EI_DATA]);
    }

    printf("  Version:                           %d", header.e_ident[EI_VERSION]);
    switch (header.e_ident[EI_VERSION]) {
        case EV_CURRENT: printf(" (current)\n"); break;
        default:         printf("\n"); break;
    }

    printf("  OS/ABI:                            ");
    switch (header.e_ident[EI_OSABI]) {
        case ELFOSABI_NONE:       printf("UNIX - System V\n"); break;
        case ELFOSABI_HPUX:       printf("UNIX - HP-UX\n"); break;
        case ELFOSABI_NETBSD:     printf("UNIX - NetBSD\n"); break;
        case ELFOSABI_LINUX:      printf("UNIX - Linux\n"); break;
        case ELFOSABI_SOLARIS:    printf("UNIX - Solaris\n"); break;
        case ELFOSABI_IRIX:       printf("UNIX - IRIX\n"); break;
        case ELFOSABI_FREEBSD:    printf("UNIX - FreeBSD\n"); break;
        case ELFOSABI_TRU64:      printf("UNIX - TRU64\n"); break;
        case ELFOSABI_ARM:        printf("ARM\n"); break;
        case ELFOSABI_STANDALONE: printf("Standalone App\n"); break;
        default:                  printf("<unknown: %x>\n", header.e_ident[EI_OSABI]);
    }

    printf("  ABI Version:                       %d\n", header.e_ident[EI_ABIVERSION]);

    printf("  Type:                              ");
    switch (header.e_type) {
        case ET_NONE:   printf("NONE (None)\n"); break;
        case ET_REL:    printf("REL (Relocatable file)\n"); break;
        case ET_EXEC:   printf("EXEC (Executable file)\n"); break;
        case ET_DYN:    printf("DYN (Shared object file)\n"); break;
        case ET_CORE:   printf("CORE (Core file)\n"); break;
        default:        printf("<unknown: %x>\n", header.e_type);
    }

    printf("  Entry point address:               %#lx\n", header.e_entry);

    close(fd);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        return 97;  // Return code 97 for incorrect number of arguments
    }

    display_elf_header(argv[1]);

    return 0;  // Return code 0 for successful execution
}

