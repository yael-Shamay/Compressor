#include "compare.h"
Bool compare() {
	char compressedFilename[MAX_PATH_LEN], decompressedFilename[MAX_PATH_LEN];
	getPathToBuffer(compressedFilename, "Enter compressed file path:");
	getPathToBuffer(decompressedFilename, "Enter decompressed file path:");
	FILE* compressFile = openFile(compressedFilename, "rb");
	FILE* deCompressFile = openFile(decompressedFilename, "rb");
	int len1 , len2;
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	len1 = readDataFromFile(buf1, BUFFER_SIZE, compressFile);
	len2 = readDataFromFile(buf2, BUFFER_SIZE, deCompressFile);
	while (len1 && len2)
	{
		buf1[len1-1] = '\0';
		buf2[len2-1] = '\0';
	    if (strcmp(buf1, buf2)==1||len1!=len2)
			return False;
		len1 = readDataFromFile(buf1, BUFFER_SIZE, compressFile);
		len2 = readDataFromFile(buf2, BUFFER_SIZE, deCompressFile);
	}
	if (len1 == len2)
		return True;
	return False;
}