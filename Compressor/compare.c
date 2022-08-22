#include "compare.h"
Bool compare() {
	FILE* compressFile = openFile(getPath(), "rb");
	FILE* deCompressFile = openFile(getPath(), "rb");
	int len1=1,len2=1;
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	while (len1 && len2)
	{
	    len1=readDataFromFile(buf1, BUFFER_SIZE, compressFile);
	  //BAG  len2=readDataFromFile(buf2, BUFFER_SIZE, deCompressFile);
		buf1[len1-1] = '\0';
		buf2[len2-1] = '\0';
		printf("buf1 %s\n", buf1);
		printf("buf2 %s\n", buf2);
	  //BAG  if (strcmp(buf1, buf2)==1)
			return False;
	}
	if (len1 == len2)
		return True;
	return False;
}

//copare
//gui
//test
//getPath 2
//האם להגדיל את buffer ל257 אול יקטין את קריאת הנתונים