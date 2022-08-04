#include "file_operaitions_API.h"

char* read_file() {
	char path[MAX_PATH_LEN] = get_path();
	char data[DATA_SIZE];
	FILE* file_ptr = open_file(path, 'r');
	fscanf(file_ptr, "%s", &data);
	printf("Value of n=%s", data);
	close_file(file_ptr);
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
void write_file(char * dataToWrite) {
	char path[MAX_PATH_LEN] = get_path();
	FILE * file_ptr = open_file(path, 'w');
	fgets(dataToWrite, sizeof(dataToWrite), stdin);
	close_file(file_ptr);
}
FILE* open_file(char* path, char mode) {
	FILE* file_ptr;
	file_ptr = fopen(path, mode);
	if (file_ptr == NULL) {
		printf("\nError file not exist!");
		exit(1);
	}
	return file_ptr;
}
void close_file(FILE* file_ptr)
{
	fclose(file_ptr);
}