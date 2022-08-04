#include "file_operaitions_API.h"
char* get_path() {
	char path[MAX_PASH];
	printf("Insert a file path\n");
	scanf("%s",&path);
	return path;
}
char* read_file() {
	char path[MAX_PASH] = get_path();
	char data[DATA_SIZE];
	FILE* file_ptr = open_file(path, 'r');
	fscanf(file_ptr, "%s", &data);
	printf("Value of n=%s", data);
	close_file(file_ptr);
	return data;
}
void write_file(char * dataToWrite) {
	char path[MAX_PASH] = get_path();
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