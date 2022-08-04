#include "deCompression.h"
#include "compression.h"
#include "compare.h"
typedef enum { COMPRESSION, DE_COMPRESSION, COMPARE, DUMMY }Option;
void menu();
void cheack_choosed_option(Option);
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
	char* outputFilePath = "outFile.myziped";
	FILE* srcFd, * outFd;
	//open2Files
	//in while loop till end of srcFile :
	///  read
	///	write
	///
	///
	//closeFiles
}
void run_choosed_option(Option selection) {
	char* file_deCompression;
	char* file_compression;
	Bool same_data;
	switch (selection)
	{
	case COMPRESSION:
		file_compression = compression();
		printf("%s", file_compression);
		return;
	case DE_COMPRESSION:
		file_deCompression = deCompression();
		printf("%s", file_deCompression);
		return;
	case COMPARE:
		same_data = compare();
		return;
	case DUMMY:
		run_dummy_case();
		return;
	default:
		printf("unsupported value");
		return;
	}
}