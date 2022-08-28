#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
void writeDataToFile(char* srcBuffer,int count, FILE* outFd);
int readDataFromFile(char* destBuffer,int count, FILE* srcFd);
FILE* openFile(char*, char*);
void closeFile(FILE*);
void writeDataToLog(FILE* logFd,char* massage);