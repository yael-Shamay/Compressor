#include "deCompression.h"
#include "compression.h"
#include "compare.h"
#include <stdio.h>
#include <stdlib.h>
/////////////////////////////file open
typedef enum { COMPRESSION, DE_COMPRESSION, COMPARE, DUMMY }Option;
#define BUFFER_SIZE 256
void menu();
void run_dummy_case();
void run_choosed_option(Option);
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
	run_choosed_option(selection);
}
void run_dummy_case() {
	char* srcFilePath = getPath();
    IsValidTextFileExtention(srcFilePath);
	char* outputFilePath ="C:\\Users\\pc\\Desktop\\project\\project\\newProject\\Compressor\\out.rmy";
	FILE* srcFd, * outFd;
	srcFd = openFile(srcFilePath,"rb");
	outFd = openFile(outputFilePath, "w+b");
	char buf[BUFFER_SIZE];
    int len;
	do {
		len = readDataFromFile(buf, 1, BUFFER_SIZE, srcFd);
		writeDataToFile(&buf,1,len, outFd);
	} while (len );
	closeFile(srcFd);
	closeFile(outFd);
}
void run_choosed_option(Option selection) {
	char* file_deCompression;
	char* file_compression;
	Bool same_data;
	switch (selection)
	{
	case COMPRESSION:
		//file_compression = compression();
		//printf("%s", file_compression);
		break;
	case DE_COMPRESSION:
		file_deCompression = deCompression();
		printf("%s", file_deCompression);
		break;
	case COMPARE:
		same_data = compare();
		break;
	case DUMMY:
		run_dummy_case();
		break;
	default:
		printf("unsupported value");
		break;
	}
}
