#define MAX_PATH_LEN 4096
#define DATA_SIZE 4096
#define EXTENTION_LEN 7
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma once
typedef enum { True, False } Bool;
char* getPath();
void getFileExtention(char*, char**);
Bool IsValidTextFileExtention(char* path);
