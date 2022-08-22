#include "utities.h"
char* getPath() {
	char path[MAX_PATH_LEN];
	printf("Insert a file path\n");
	getchar();
	gets(path);
	puts(path);
	return path;
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
	printf("error type");
	exit(1);
	return False;
}
void getReletivePath(const char* srcPath, char** desPath) {
	printf("%s", srcPath);
	int indexCat = 0;
	char newPath[MAX_PATH_LEN];
	for (size_t i = 0; i < strlen(desPath); i++)
	{
		if (desPath[i] == '\\')
			indexCat = i;
		newPath[i] = desPath[i];
	}
	newPath[indexCat] = '\0';
	//strcat(newPath,"out.rmy");
	*desPath = newPath;
}
//char* getReletivePath(const char* srcPath) {
//	printf("%s",srcPath);
//	int indexCat = 0;
//	char desPath[MAX_PATH_LEN];
//	for (size_t i = 0; i < strlen(srcPath); i++)
//	{
//		if (srcPath[i] == '\\')
//			indexCat = i;
//		desPath[i] = srcPath[i];
//	}
//	desPath[indexCat + 1] = '\0';
//	//strcat(desPath,"out.rmy");
//	return desPath;
//}