#define _CRT_SECURE_NO_WARNINGS
#define MAX_PATH_LEN 4096
#define DATA_SIZE 4096
#define EXTENTION_LEN 7
#define BUFFER_SIZE 256
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma once
typedef enum { True, False } Bool;
char* getPath();
void getFileExtention(const char*, char**);
Bool isValidTextFileExtention(const char* path);
void getReletivePath(const char* srcPath, char** desPath);
//char* getReletivePath(const char* srcPath);