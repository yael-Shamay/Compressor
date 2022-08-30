#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>    
#include <errno.h>
#include "fileOperaitionAPI.h"
#pragma once

#define MAX_PATH_LEN 4096
#define DATA_SIZE 4096
#define EXTENTION_LEN 7
#define BUFFER_SIZE 256
#define MASSAGE_LEEN 256
char massage[256];
FILE* logFd;

typedef enum { False, True } Bool;
void getPathToBuffer(char* pathBuffer,char* enterPathMessage);
void getFileExtention(const char*, char**);
Bool isValidTextFileExtention(const char* path);
void getReletivePath(char* srcPath, char* desPath);
void createPathToInputFile(char* srcPath, char* desPath);
//char* convertEnumToString(Option select);
void createLogFile();
void writeToLog(char* massage);
void closeLog();