#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "utities.h"
void writeDataToFile(char* srcBuffer,int count, FILE* outFd);
int readDataFromFile(char* destBuffer,int count, FILE* srcFd);
FILE* openFile(char*, char*);
void closeFile(FILE*);