
#include "lzw.h"
#include "compare.h"
#include <stdio.h>
#include <stdlib.h>
typedef enum { COMPRESSION, DE_COMPRESSION, COMPARE, DUMMY }Option;

#define BUFFER_SIZE 256
char logFilePath[] = "C:\\Users\\pc\\Desktop\\project\\project\\new\\Compressor\\log.txt";
FILE* logFd;
void menu();
 void lzw_writebuf(void* stream, char* buf, unsigned size)
{
	 if (stream != NULL)
	    fwrite(buf, size, 1, (FILE*)stream);
}
 unsigned lzw_readbuf(void* stream, char* buf, unsigned size)
{
	 unsigned t;
	 if (stream != NULL) {
		 t = fread(buf, 1, size, (FILE*)stream);
		 
	 }
	 return t;

}
void runDummyCase();
void runChoosedOption(Option);
void main() {
	//open log file
	logFd = openFile(logFilePath, "w");
	if (logFd == NULL) {
		printf("error logFile not open");
		//exit(-1);
	}
	menu();
	closeFile(logFd);
}
void menu() {
	Option selection;
	printf("press 0 to compresstion\n");
	printf("press 1 to deCompresstion\n");
	printf("press 2 to compare two files\n");
	printf("press 3 for dummy\n");
	scanf_s("%d", &selection);
	writeDataToLog(logFd,"option select : ");
	writeDataToLog(logFd,(char*)selection);
	runChoosedOption(selection);
}
void runDummyCase() {
	char srcFilePath[MAX_PATH_LEN];
	getPathToBuffer(srcFilePath,"Enter file path to run dummy:");
	writeDataToLog(logFd,"\nthe srcPath is :  ");
	writeDataToLog(logFd,srcFilePath);
	char outputFilePath[MAX_PATH_LEN];
	if (!isValidTextFileExtention(srcFilePath))
	{
		printf("File type error\n");
   		exit(1);
	}
	createPathToInputFile(srcFilePath, outputFilePath);
	writeDataToLog(logFd, "\nthe outputPath is :  ");
	writeDataToLog(logFd, outputFilePath);
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
	//closeFile(logFd);
}


void runChoosedOption(Option selection) {
	char* fileDeCompression;
	char* fileCompression;
	Bool isSamedata;
	switch (selection)
	{
	case COMPRESSION:
		compressionProcess();
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
