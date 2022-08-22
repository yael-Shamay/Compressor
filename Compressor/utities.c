#include "utities.h"
//TODO remove this function
char* getPath() {
	printf("remove this function\n");
	return 0;
	char path[MAX_PATH_LEN];
	printf("Insert a file path\n");
	getchar();
	scanf("%s",path);
	puts(path);
	return path;
}
void getPathToBuffer(char* pathBuffer, char* enterPathMessage) {
	printf(enterPathMessage);
	printf("\n");
	getchar();
	scanf("%s", pathBuffer);
	//TODO - remove later
	puts(pathBuffer);
}
void getFileExtention(const char* filePath, char** extention)
{
	*extention = strchr(filePath, '.');
	/*printf("\n------path----------");
	printf("\n%s", filePath);
	printf("\n------extention----------");
	printf("\n%s",*extention);*/
}
Bool isValidTextFileExtention(const char* path) {
	char* fileExtention;
	char* validTextExtentions[EXTENTION_LEN] = { "c","cpp","css","py","txt","java" };
	getFileExtention(path,&fileExtention);
	//remove the first char '.'
	fileExtention += 1;
	printf("\n%s",fileExtention);
	for (int i = 0; i < sizeof(validTextExtentions)-1 / EXTENTION_LEN; i++)
	{
		if (strcmp(fileExtention,validTextExtentions[i])==0)
			return True;
	}
	return False;
}
void getReletivePath(char* srcPath, char** desPath) {
	printf("%s", srcPath);
	int indexCat = 0;
	char newPath[MAX_PATH_LEN];
	int len = strlen(srcPath);
	for (int i = 0; i < len; i++)
	{
		if (srcPath[i] == '\\')
			indexCat = i;
		newPath[i] = srcPath[i];
	}
	newPath[indexCat] = '\0';
	//strcat(newPath,"out.rmy");
	*desPath = newPath;
}
