#include "fileOperaitionAPI.h"
int readDataFromFile(char* destBuffer,int count, FILE* srcFd) {
 return	fread(destBuffer, 1, count, srcFd);
}
void writeDataToFile(char* srcBuffer,int count, FILE* outFd) {
	fwrite(&srcBuffer, 1, count, outFd);
}
FILE* openFile(char* path, char *mode) {
	FILE* filePtr= fopen(path,mode);
	if (filePtr == NULL) {
		printf("\nError file not exist!");
		exit(1);
	}
	return filePtr;
}
void closeFile(FILE* file_ptr)
{
	fclose(file_ptr);
}