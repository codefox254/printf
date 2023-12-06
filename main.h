#ifndef __MAIN_H__
#define __MAIN_H__

#include <elf.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void display_error_and_exit(const char *error_message);
void display_elf_header(const char *filename);

#endif

