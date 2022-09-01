
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
TEST_RANDOM5MB,
#endif
NUM_OF_OPTIONS // must be always last
}Option;

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
	writeToLog("enter to project\n");
	menu();
	closeLog();
}

void menu() {
	Option selection;
	char  options[NUM_OF_OPTIONS][256] = { "compression","deCompresstion","compare","dummy","TEST_CREATE1GB","TEST_CREATE4KB", "Test_random5MB"};
	printf("The options are:\n");
	for (int i = 0; i < NUM_OF_OPTIONS; i++)
	{
		printf("\tpress %d for %s\n",i, options[i]);
	}
	scanf_s("%d", &selection);
	sprintf(massage, "the selection option %s case , time is :%s\n", options[selection], getTime());
	writeToLog(massage);
	runChoosedOption(selection);
}
void runDummyCase() {
	char srcFilePath[MAX_PATH_LEN];
	getPathToBuffer(srcFilePath,"Enter file path to run dummy:");
	sprintf(massage,"the srcPath is :  %s . time is %s\n", srcFilePath, getTime());
	writeToLog(massage);

	char outputFilePath[MAX_PATH_LEN];
	if (!isValidTextFileExtention(srcFilePath))
	{
		writeToLog("file type error\n");
		printf("File type error\n");
   		exit(1);
	}
	createPathToInputFile(srcFilePath, outputFilePath);

	sprintf(massage, "the outputPath is :  %s\n", outputFilePath);
	writeToLog(massage);

	FILE* srcFd,* outFd;
	srcFd = openFile(srcFilePath,"rb");
	writeToLog("success open src file\n");
	outFd = openFile(outputFilePath, "w+b");
	writeToLog("success open output file\n");
	char buf[BUFFER_SIZE];
    int len;
	sprintf(massage, "start read data to buffer and writethe buffer to file ,time is :%s\n", getTime());
	writeToLog(massage);
	do {
		len = readDataFromFile(buf,BUFFER_SIZE, srcFd);
		writeDataToFile(&buf,len, outFd);
	} while(len);
	sprintf(massage, "end read data to buffer and writethe buffer to file ,time is :%s\n", getTime());
	writeToLog(massage);
	closeFile(srcFd);
	closeFile(outFd);
	writeToLog("success close src and output file files\n");
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
		isSamedata ? printf("the data in the files is same "):
			printf("there is diffrance betwen the files ");
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
	case TEST_RANDOM5MB:
		test_runRandom5MB();
		break;
	default:
		printf("unsupported value");
		break;
	}
}
