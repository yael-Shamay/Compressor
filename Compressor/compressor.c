#include "deCompression.h"
#include "compression.h"
#include "compare.h"
typedef enum { COMPRESSION, DE_COMPRESSION, COMPARE }Option;
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
	scanf("%d", &selection);
	cheack_choosed_option(selection);
}
void cheack_choosed_option(Option selection) {
	char* file_deCompression;
	char* file_compression;
	Bool same_data;
	switch (selection)
	{
	case COMPRESSION:
	{
		file_compression = compression();
		printf("%s", file_compression);
	}
	return;
	case DE_COMPRESSION:
	{
		file_deCompression = deCompression();
		printf("%s", file_deCompression);
	}
	return;
	case COMPARE:
		same_data = compare();
		return;
	default:
		printf("unsupported value");
		return;
	}
}