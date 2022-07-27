#include "file_operation_API.h"
void write_file() {
	FILE* file_ptr;
    char sentence[1000];
	file_ptr = open_file(get_path());
    printf("Enter a sentence:\n");
    fgets(sentence, sizeof(sentence), stdin);
    fprintf(file_ptr,"%s", sentence);
    close_file(file_ptr);
}
void read_file() {

}
char* get_path() {
	char* path_file;
	printf("Insert a file path");
	scanf("%[^\n]%*c", &path_file);
	return path_file;
}
FILE * open_file(char * path_file) {
    FILE* file_ptr;
    file_ptr = fopen(path_file, "w");
    // exiting program 
    if (file_ptr == NULL) {
        printf("\nError!");
        exit(1);
    }
    return file_ptr;
}
void close_file(FILE* file_ptr) {
    fclose(file_ptr);
}
