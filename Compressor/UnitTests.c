#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _FILE_OFFSET_BITS 64

#define KB 1024

char bufferPattern[KB] = {0};

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

//I did it just 1MB KB*KB is MB
void test_run1GB() {
   printf("creating file ....\n");
   fillbufferPattern("ABCD", 4);
   createFile("File_1GB_ABCD.txt", KB * KB);
   printf("finished to fill file\n");
   //here will be the test

}

void test_run4KB() {
   printf("creating file ....\n");
   fillbufferPattern("TGH?", 4);
   createFile("File_4KB_TGH_.txt", 4 * KB);
   printf("finished to fill file\n");
   //here will be the test
}
