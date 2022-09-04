#include "compare.h"
Bool compare() {
	char compressedFilename[MAX_PATH_LEN], decompressedFilename[MAX_PATH_LEN];
	getPathToBuffer(compressedFilename, "Enter compressed file path:");
	getPathToBuffer(decompressedFilename, "Enter decompressed file path:");
	Bool isSamedata =compareWithPath(compressedFilename,decompressedFilename);
	isSamedata ? writeToLog("the data in the files is same ") :
		writeToLog("there is diffrance betwen the files ");
	writeToLog(massage);
	return isSamedata;
}
Bool compareWithPath(char* compressedFilename,char* decompressedFilename) {
	sprintf(massage, "file yo compare :\ncompressed file path : %s\n compressed file path : %s\n", compressedFilename,decompressedFilename);
	writeToLog(massage);
	char decompressCompressedFilename[MAX_PATH_LEN];
	createPathToInputFile(compressedFilename, decompressCompressedFilename);
	sprintf(massage, "create deCompress file from files compress\npath new deCompress file : %s\n ", decompressCompressedFilename);
	writeToLog(massage);
	decompressProcces(compressedFilename, decompressCompressedFilename);
	FILE* compressFile = openFile(decompressCompressedFilename, "rb");
	FILE* deCompressFile = openFile(decompressedFilename, "rb");
	writeToLog("open file success\n");
	writeToLog("comparing...\n");
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