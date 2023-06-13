#pragma once
#include "utities.h"
void fillBufferRandomPattern();
void fillbufferPattern(char* pattern, int size);
void createFile(char* filname, int sizeInKB);
void createRandomFile(char* filname, int sizeInBytes);
void test_run1GB();
void test_run4KB();
void test_runRandom5MB();
void test_runEmpty();
void test_runpathIncludePoints();
void test_runSpecialCharacters();