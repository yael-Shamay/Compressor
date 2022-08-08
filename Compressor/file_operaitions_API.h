#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "utities.h"

char* readFile();
char* data_To_write();
void writeFile();
FILE* openFile(char*, char*);
FILE* openFile1(char*, char*);
void closeFile(FILE*);