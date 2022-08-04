#include "utities.h"

char* getPath() {
	char path[MAX_PATH_LEN];
	printf("Insert a file path\n");
	scanf_s("%s", path);
	return path;
}

void getFileExtention(char* filePath, char* extention)
{

}
int IsValidTextFileExtention(char* path) {
	char fileExtention[7];
	char validTextExtentions[] = { "ag","aarg" };
	getFileExtention(path, fileExtention);


	//go in loop 

}