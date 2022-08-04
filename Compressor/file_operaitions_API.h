#define _CRT_SECURE_NO_WARNINGS
#define MAX_PASH 256
#define DATA_SIZE 4096
#include <stdio.h>
#include <stdlib.h>
#include "utities.h"
char* get_path();
char* read_file();
char* data_To_write();
void write_file();
FILE* open_file(char*, char);
void close_file(FILE*);