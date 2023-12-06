#include "main.h"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
        return 98; // Exit with status code 98 for incorrect usage
    }

    display_elf_header(argv[1]);

    return 0; // Exit with status code 0 for successful execution
}

