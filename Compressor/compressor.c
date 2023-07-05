
#include "lzw.h"
#include "compare.h"
#include "utities.h"
#include "Tests.h"
#include <stdio.h>
#include <stdlib.h>
#define tested_version
#define EXEC_VERSION

typedef enum 
{ COMPRESSION,
DE_COMPRESSION,
COMPARE,
#ifdef tested_version
DUMMY,
TEST_CREATE1GB,
TEST_CREATE4KB,
TEST_RANDOM5MB,
TEST_EMPTYFILE,
TEST_SPECIAL_CHARACTERS,
TEST_PATH_INCLUDE_POINTS,
#endif
NUM_OF_OPTIONS // must be always last
}Option;

int getUserInput();
int getCommandInput(char option);
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
 int runOptionFromUI(int option, char* path1, char* path2)
 {
	 char outFileName[MAX_PATH_LEN];
	 Bool isSamedata = 0;
	 switch (option)
	 {
	 case 0:
		 createPathToInputFile(path1, outFileName);
		 compressFile(path1, outFileName);
		 break;
	 case 1:
		 createPathToInputFile(path1, outFileName);
		 decompressProcces(path1, outFileName);
		 break;
	 case 2:
		 isSamedata = compareWithPath(path1, path2);
		 isSamedata ? printf("the data in the files is same ") : printf("there is diffrance betwen the files ");
	 default:
		 break;
	 }
	 return 1;
 }
void runDummyCase();
void runChoosedOption(Option);
// script_name.exe option src_file out_file  (0-compress 1-decompress 2-compare)
void main(int argc, char	*argv[]) {
	int ret;
#ifdef EXEC_VERSION
	if (argc < 2)
	{
		printf("missed option");
		exit(1);
	}
	printf("The argument supplied is %s\n", argv[1]);
#endif
	createLogFile();
	writeToLog("enter to project\n");
#ifdef EXEC_VERSION
	int selection = getCommandInput(argv[1][0]);
	printf("selection is %d\n", selection);
#else
	int selection = getUserInput();
	runChoosedOption(selection);
#endif // EXEC_VERSION

#ifdef EXEC_VERSION
	ret = runOptionFromUI(selection, argv[2], argv[3]);
#endif
	closeLog();
	return 0;
}
int getCommandInput(char option) {
	//switch (option)
	//{
	//case '1':
	//	return 1;
	//default:
	//	break;
	//}
	return option - '0';
}

int getUserInput() {
	Option selection;
	char  options[NUM_OF_OPTIONS][256] = { "COMPRESSION","DE_COMPRESSION","COMPARE","DUMMY","TEST_CREATE1GB","TEST_CREATE4KB", "TEST_RANDOM5MB","TEST_EMPTYFILE","TEST_SPECIAL_CHARACTERS","TEST_PATH_INCLUDE_POINTS"};
	printf("The options are:\n");
	for (int i = 0; i < NUM_OF_OPTIONS; i++)
	{
		printf("\tpress %d for %s\n",i, options[i]);
	}
	scanf_s("%d", &selection);
	sprintf(massage, "the selection option %s case , time is :%s\n", options[selection], getTime());
	writeToLog(massage);
	return selection;	
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
		break;
	case DE_COMPRESSION:
		 deCompression();
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
	case TEST_EMPTYFILE:
		test_runEmpty();
		break;
	case TEST_SPECIAL_CHARACTERS:
		test_runSpecialCharacters();
		break;
	case TEST_PATH_INCLUDE_POINTS:
		test_runpathIncludePoints();
		break;
	default:
		printf("unsupported value");
		break;
	}
}
