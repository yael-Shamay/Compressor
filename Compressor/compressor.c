#include "deCompression.h"
#include "compression.h"
#include "compare.h"
#include <stdio.h>
#include <stdlib.h>
typedef enum { COMPRESSION, DE_COMPRESSION, COMPARE, DUMMY }Option;
//#define BUFFER_SIZE 256
void menu();
void runDummyCase();
void runChoosedOption(Option);
void main() {
	menu();
}
void menu() {
	Option selection;
	printf("press 0 to compresstion\n");
	printf("press 1 to deCompresstion\n");
	printf("press 2 to compare two files\n");
	printf("press 3 for dummy\n");
	scanf_s("%d", &selection);
	runChoosedOption(selection);
}
void runDummyCase() {
	char* srcFilePath = getPath();
    isValidTextFileExtention(srcFilePath);
	printf("%s", srcFilePath);
	char outputFilePath[MAX_PATH_LEN];
	getReletivePath(srcFilePath,&outputFilePath);
	printf("%s - srcFilePath", srcFilePath);
	printf("%s - outputFilePath", outputFilePath);
//	char* outputFilePath = getReletivePath(srcFilePath);
	FILE* srcFd,* outFd;
	srcFd = openFile(srcFilePath,"rb");
	outFd = openFile(outputFilePath, "w+b");
	char buf[BUFFER_SIZE];
    int len;
	do {
		len = readDataFromFile(buf,BUFFER_SIZE, srcFd);
		writeDataToFile(&buf,len, outFd);
	} while(len);
	closeFile(srcFd);
	closeFile(outFd);
}
void runChoosedOption(Option selection) {
	char* fileDeCompression;
	char* fileCompression;
	Bool isSamedata;
	switch (selection)
	{
	case COMPRESSION:
		//fileCompression = compression();
		//printf("%s", fileCompression);
		break;
	case DE_COMPRESSION:
		fileDeCompression = deCompression();
		printf("%s", fileDeCompression);
		break;
	case COMPARE:
		isSamedata = compare();
		isSamedata ? printf("there is diffrance betwen the files "):
			printf("the data in the files is same ") ;
		break;
	case DUMMY:
		runDummyCase();
		break;
	default:
		printf("unsupported value");
		break;
	}
}
