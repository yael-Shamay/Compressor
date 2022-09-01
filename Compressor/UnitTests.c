#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Tests.h"
#include <time.h>
#include "lzw.h"

#define _FILE_OFFSET_BITS 64

#define KB 1024

char bufferPattern[KB] = {0};

void fillBufferRandomPattern() {
	int index = 0;
	char y = "";
	int randModule = rand() % 256;
	while (index < KB) {
		
		bufferPattern[index++] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL MNOPQRSTUVWXYZ"[rand() % randModule];// (rand() % (89 -67)) + 0;
	}

}

//size must be alighned to 4
void fillbufferPattern(char* pattern, int size)
{
   if (KB % size)
   {
      printf("Wrong pattern size");
      return;
   }
   char* pBuffer = bufferPattern;
   for (int i = 0; i < KB;i+=size)
   {
      memcpy(pBuffer, pattern, size);
      //TODO -- check that it changes the pointer well
      pBuffer += size;
   }
}

void createFile(char* filname, int sizeInKB)
{
   FILE* fd = fopen(filname, "w");
   if (fd == NULL)
   {
      printf("can't create %s\n", filname);
      exit(-1);
   }

   while (sizeInKB--)
   {
      fwrite(bufferPattern, 1, KB, fd);
   }
   fclose(fd);
}

void createRandomFile(char* filname, int sizeInBytes)
{
	FILE* fd = fopen(filname, "w");
	if (fd == NULL)
	{
		printf("can't create %s\n", filname);
		exit(-1);
	}

	int x = 1;
	char y = "";
	while (x < sizeInBytes) {

		y = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKL MNOPQRSTUVWXYZ"[rand() % 53];// (rand() % (89 -67)) + 0;
		fprintf(fd, "%c", y);
		x++;
	}
	fclose(fd);
}


void test_run1GB() {
   printf("creating file ....\n");
   fillbufferPattern("ABCD", 4);
   char inputFileName[] = "File_1GB_ABCD.txt";
   createFile(inputFileName, KB * KB);
   printf("finished to fill file\n");
   char outFileName[256];
   createPathToInputFile(inputFileName, outFileName);
   Bool isSamedata = compareWithPath(inputFileName, outFileName);
   isSamedata ? printf("the data in the files is same ") :
       printf("there is diffrance betwen the files \n");
   printf("success test\n");
}

void test_run4KB() {
   printf("creating file ....\n");
   fillbufferPattern("TGH?", 4);
   createFile("File_4KB_TGH_.txt", 4 * KB);
   printf("finished to fill file\n");
   //here will be the test
}

void test_runRandom5MB() {
	printf("creating file ....\n");
	//fillBufferRandomPattern();
	char filename[] = "File_5MB.txt";
	//createFile(filename,KB*5);
	createRandomFile(filename, 5 * KB * KB);
	printf("finished to fill file\n");
	//here will be the test
}

//byte = 1
//KB = 1024
//MB = 1024 *KB
//GB = 1024 *MB
