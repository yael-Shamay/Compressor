#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS_GLOBALS
#pragma warning(disable:4996)
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
#define TIME_SIZE 14
char massage[256];
FILE* logFd;
char time_buf[TIME_SIZE];

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
char* getTime();