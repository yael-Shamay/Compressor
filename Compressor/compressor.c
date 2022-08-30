
#include "lzw.h"
#include "compare.h"
#include "utities.h"
#include <stdio.h>
#include <stdlib.h>
typedef enum { COMPRESSION, DE_COMPRESSION, COMPARE, DUMMY }Option;

#define BUFFER_SIZE 256
//char logFilePath[] = "Logs\\log.txt";
//FILE* logFd;
void menu();
void lzwWritebuf(void* outFile, char* buf, unsigned size)
{
	fwrite(buf, size, 1, (FILE*)outFile);
}

unsigned lzwReadbuf(void* outFile, char* buf, unsigned size)
{
	unsigned t = fread(buf, 1, size, (FILE*)outFile);

	return t;
}

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
	createLogFile();
	writeToLog("enter to project");
	menu();
	closeLog();
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
	char srcFilePath[MAX_PATH_LEN];
	getPathToBuffer(srcFilePath,"Enter file path to run dummy:");
	writeToLog("\nthe srcPath is :  ");
	writeToLog(srcFilePath);

	/*char massage[256];
	sprintf(massage,"\nthe srcPath is :  %s",srcFilePath);
	writeToLog(massage);*/

	char outputFilePath[MAX_PATH_LEN];
	if (!isValidTextFileExtention(srcFilePath))
	{
		writeToLog("\nfile type error");
		printf("File type error\n");
   		exit(1);
	}
	createPathToInputFile(srcFilePath, outputFilePath);
	writeToLog("\nthe outputPath is :  ");
	writeToLog(outputFilePath);
	FILE* srcFd,* outFd;
	srcFd = openFile(srcFilePath,"rb");
	writeToLog("\nsuccess open src file");
	outFd = openFile(outputFilePath, "w+b");
	writeToLog("\nsuccess open output file");
	char buf[BUFFER_SIZE];
    int len;
	writeToLog("\nstart read data to buffer and writethe buffer to file");
	do {
		len = readDataFromFile(buf,BUFFER_SIZE, srcFd);
		writeDataToFile(&buf,len, outFd);
	} while(len);
	writeToLog("\nend read data to buffer and writethe buffer to file");
	closeFile(srcFd);
	closeFile(outFd);
	writeToLog("\nsuccess close src and output file files");
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
		printf("hello I am in dec");
		 deCompression();
		//printf("%s", fileDeCompression);
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
