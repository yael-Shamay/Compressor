#include "utities.h"
//TODO remove this function
char* getPath() {
	printf("remove this function\n");
	return 0;
	char path[MAX_PATH_LEN];
	printf("Insert a file path\n");
	getchar();
	scanf("%s",path);
	return path;
}
void getPathToBuffer(char* pathBuffer, char* enterPathMessage) {
	printf(enterPathMessage);
	printf("\n");
	getchar();
	scanf("%s", pathBuffer);
	//TODO - remove later
}
void getFileExtention(const char* filePath, char** extention)
{
	for (size_t i = 0; i < strlen(filePath); i++)
	{
		if (filePath[i] == '.')
			*extention = filePath + i;
	}
}
Bool isValidTextFileExtention(const char* path) {
	char* fileExtention;
	char* validTextExtentions[EXTENTION_LEN] = { "c","cpp","css","py","txt","java" };
	getFileExtention(path,&fileExtention);
	fileExtention += 1;
	for (int i = 0; i < sizeof(validTextExtentions)-1 / EXTENTION_LEN; i++)
	{
		if (strcmp(fileExtention,validTextExtentions[i])==0)
			return True;
	}
	return False;
}
void getReletivePath(char* srcPath, char* desPath) {
	int indexCat = 0;
	int len = strlen(srcPath);
	for (int i = 0; i < len; i++)
	{
		if (srcPath[i] == '\\')
			indexCat = i;
		desPath[i] = srcPath[i];
	}
	desPath[indexCat] = '\0';
}
