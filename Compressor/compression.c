#include "compression.h"
char* compression() {
	char dataToCompress[DATA_SIZE] = read_file();
	printf("%s", dataToCompress);
}
