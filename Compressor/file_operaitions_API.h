#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "utities.h"

char* read_file();
char* data_To_write();
void write_file();
FILE* open_file(char*, char);
void close_file(FILE*);