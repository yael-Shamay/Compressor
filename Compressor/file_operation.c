#include "file_operaitions_API.h"

char* readFile() {
	char* path = getPath();
	char data[DATA_SIZE];
	FILE* file_ptr = openFile(path, "r");
	fscanf(file_ptr, "%s", &data);
	printf("Value of n=%s", data);
	closeFile(file_ptr);
	return data;
}
void readDataFromFile(FILE* fd,char* destBuffer,int size) {
	//Add read call with size
	fread(destBuffer, size, 1, fd);
}
void writeDataToFile(FILE* out_fd, char* srcBuffer, int size) {
	//Add read call with size
	fwrite(srcBuffer, size, 1, out_fd);
}
void writeFile(char * dataToWrite) {
	char* path= getPath();
	FILE * file_ptr = openFile(path, "w");
	fgets(dataToWrite, sizeof(dataToWrite), stdin);
	closeFile(file_ptr);
}
FILE* openFile(char* path, char *mode) {
	///////////why a in valid and path is faild
	FILE* file_ptr;
	//printf("\n path file src %s",path);
	char* a = "C:\\Users\\pc\\Desktop\\project\\project\\newProject\\Compressor\\srcFile.txt";
	//printf("\n path file src %s", a);
	file_ptr = fopen(a,mode);
	//file_ptr = fopen(path,mode);
	if (file_ptr == NULL) {
		printf("\nError file not exist!");
		exit(1);
	}
	return file_ptr;
}
FILE* openFile1(char* path, char* mode) {
	FILE* file_ptr;
	file_ptr = fopen(path, mode);
	if (file_ptr == NULL) {
		printf("\nError file not exist!");
		exit(1);
	}
	return file_ptr;
}
void closeFile(FILE* file_ptr)
{
	fclose(file_ptr);
}