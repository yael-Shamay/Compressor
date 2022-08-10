#include "file_operaitions_API.h"
int readDataFromFile(char* destBuffer,int size,int count, FILE* srcFd) {
 return	fread(destBuffer, size, count, srcFd);
}
void writeDataToFile(char* srcBuffer, int size,int count, FILE* outFd) {
	fwrite(&srcBuffer, size, count, outFd);
}
FILE* openFile(char* path, char *mode) {
	FILE* file_ptr;
	file_ptr = fopen(path,mode);
	if (file_ptr == NULL) {
		printf("\nError file not exist!");
		exit(1);
	}
	return file_ptr;
}
void closeFile(FILE* file_ptr)
{
	fclose(file_ptr);
}