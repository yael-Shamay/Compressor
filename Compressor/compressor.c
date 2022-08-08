#include "deCompression.h"
#include "compression.h"
#include "compare.h"
/////////////////////////////file open
typedef enum { COMPRESSION, DE_COMPRESSION, COMPARE, DUMMY }Option;
#define BUFFER 256
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
	char* outputFilePath ="C:\\Users\\pc\\Desktop\\project\\project\\newProject\\Compressor\\outFile.txt";
	printf("\n%s", outputFilePath );
	FILE* srcFd, * outFd;
	//open2Files
	srcFd = openFile(srcFilePath, "r");//rb
	outFd = openFile1(outputFilePath,"w");
	//in while loop till end of srcFile :
	///  read
	char buf[BUFFER];
	while (fgets(buf, sizeof(BUFFER), srcFd) != NULL) {
	///	write
		fputs(buf, outFd);
	}
	//closeFiles
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