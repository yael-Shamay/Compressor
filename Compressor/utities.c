#include "utities.h"
char* getPath() {
	char path[MAX_PATH_LEN];
	printf("Insert a file path\n");
	getchar();
	gets(path);
	return path;
}
void getFileExtention(char* filePath, char** extention)
{
	*extention = strchr(filePath, '.');
	/*printf("\n------path----------");
	printf("\n%s", filePath);
	printf("\n------extention----------");
	printf("\n%s",*extention);*/
}
Bool IsValidTextFileExtention(char* path) {
	char* fileExtention;
	char* validTextExtentions[EXTENTION_LEN] = { "c","cpp","css","py","txt","java" };
	getFileExtention(path,&fileExtention);
	//remove the first char '.'
	fileExtention+=1;
	printf("\n%s",fileExtention);
	for (int i = 0; i < sizeof(validTextExtentions)-1 / EXTENTION_LEN; i++)
	{
		if (strcmp(fileExtention,validTextExtentions[i])==0)
			return True;
	}
	printf("error type");
	return False;
}
char* getReletivePath(char srcPath[]) {
	int indexCat = 2;
	char* desPath = srcPath;
	for (size_t i = 0; i < strlen(srcPath); i++)
	{
		if (srcPath[i] == '\\')
			indexCat = i;
	}
	desPath[indexCat + 1] = '\0';
	return srcPath;
}