#include "compare.h"
Bool compare() {
	char compressedFilename[MAX_PATH_LEN], decompressedFilename[MAX_PATH_LEN];
	getPathToBuffer(compressedFilename, "Enter compressed file path:");
	getPathToBuffer(decompressedFilename, "Enter decompressed file path:");
	Bool b=compareWithPath(compressedFilename,decompressedFilename);
	return b;
}
Bool compareWithPath(char* compressedFilename,char* decompressedFilename) {
	printf("compressedFilename%s\ndecompressedFilename%s\n", compressedFilename, decompressedFilename);
	char decompressCompressedFilename[MAX_PATH_LEN];
	createPathToInputFile(compressedFilename, decompressCompressedFilename);
	decompressProcces(compressedFilename, decompressCompressedFilename);
	FILE* compressFile = openFile(decompressCompressedFilename, "rb");
	FILE* deCompressFile = openFile(decompressedFilename, "rb");
	int len1, len2;
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	len1 = readDataFromFile(buf1, BUFFER_SIZE, compressFile);
	len2 = readDataFromFile(buf2, BUFFER_SIZE, deCompressFile);
	while (len1 && len2)
	{
		buf1[len1 - 1] = '\0';
		buf2[len2 - 1] = '\0';
		if (strcmp(buf1, buf2) == 1 || len1 != len2)
			return False;
		len1 = readDataFromFile(buf1, BUFFER_SIZE, compressFile);
		len2 = readDataFromFile(buf2, BUFFER_SIZE, deCompressFile);
	}
	if (len1 == len2)
		return True;
	return False;
}