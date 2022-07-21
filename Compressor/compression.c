#include "compression.h"
void writeToFile()
{
    char sentence[1000];
    // creating file pointer to work with files
    FILE* fptr;
    // opening file in writing mode
    //fptr = fopen("program.txt", "w");
    fptr = fopen("C:\\Users\\pc\\Desktop\\project\\writeToFile.txt", "w");
    // exiting program 
    if (fptr == NULL) {
        printf("\nError!");
        exit(1);
    }
    printf("Enter a sentence:\n");
    fgets(sentence, sizeof(sentence), stdin);
    fprintf(fptr, "%s", sentence);
    fclose(fptr);
}
