
#include "lzw.h"
#include "compare.h"
#include "utities.h"
#include "Tests.h"
#include <stdio.h>
#include <stdlib.h>
#define tested_version

typedef enum 
{ COMPRESSION,
DE_COMPRESSION,
COMPARE,
#ifdef tested_version
DUMMY,
TEST_CREATE1GB,
TEST_CREATE4KB,
#endif
NUM_OF_OPTIONS // must be always last
}Option;

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
	createLogFile();
	writeToLog("enter to project");
	menu();
	closeLog();
}

void menu() {
	Option selection;
	char  options[NUM_OF_OPTIONS][256] = { "compression","deCompresstion","compare","dummy","TEST_CREATE1GB","TEST_CREATE4KB"};
	printf("The options are:\n");
	for (int i = 0; i < NUM_OF_OPTIONS; i++)
	{
		printf("\tpress %d for %s\n",i, options[i]);
	}
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
	case TEST_CREATE1GB:
		test_run1GB();
		break;
	case TEST_CREATE4KB:
		test_run4KB();
		break;
	default:
		printf("unsupported value");
		break;
	}
}
