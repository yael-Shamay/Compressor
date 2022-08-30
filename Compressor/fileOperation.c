#include "fileOperaitionAPI.h"
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
int readDataFromFile(char* destBuffer,int count, FILE* srcFd) {
 return	fread(destBuffer, 1, count, srcFd);
}
void writeDataToFile(char* srcBuffer,int count, FILE* outFd) {
	fwrite(&srcBuffer, 1, count, outFd);
}
FILE* openFile(char* path, char* mode) {
	FILE* filePtr= fopen(path,mode);
	if (filePtr == NULL) {
		printf("\nError file not exist!");
		//exit(1);
	}
	return filePtr;
}
FILE* openLogFile(char* path,char* mode) {
	FILE* filePtr = fopen(path, mode);
	if (filePtr == NULL) {
		printf("\n failed to create log file , error %d", errno);
	}
	return filePtr;
}
void closeFile(FILE* file_ptr)
{
	if (file_ptr != NULL)
	fclose(file_ptr);
}
void writeDataToLog(FILE* logFd, char* massage){
	fputs(massage, logFd);
}