#include "utities.h"
//TODO remove this function
char* getPath() {
	printf("remove this function\n");
	return 0;
	char path[MAX_PATH_LEN];
	printf("Insert a file path\n");
	getchar();
	scanf("%s", path);
	return path;
}
void getPathToBuffer(char* pathBuffer, char* enterPathMessage) {
	printf(enterPathMessage);
	printf("\n");
	getchar();
	scanf("%s", pathBuffer);
	//TODO - remove later
}
void getFileExtention(const char* filePath, char** extention)
{
	for (size_t i = 0; i < strlen(filePath); i++)
	{
		if (filePath[i] == '.')
			*extention = filePath + i;
	}
}
Bool isValidTextFileExtention(const char* path) {
	char* fileExtention;
	char* validTextExtentions[EXTENTION_LEN] = { "c","cpp","css","py","txt","java","rmy" };
	getFileExtention(path, &fileExtention);
	fileExtention += 1;
	int len = sizeof(validTextExtentions) / sizeof(validTextExtentions[0]);
	for (int i = 0; i < len; i++)
	{
		if (strcmp(fileExtention, validTextExtentions[i]) == 0)
			return True;
	}
	return False;
}
void getReletivePath(char* srcPath, char* desPath) {
	int indexCat = 0;
	int len = strlen(srcPath);
	for (int i = 0; i < len; i++)
	{
		if (srcPath[i] == '.')
			indexCat = i;
		desPath[i] = srcPath[i];
	}
	desPath[indexCat] = '\0';
}
void createPathToInputFile(char* srcPath, char* desPath) {
	getReletivePath(srcPath, desPath);
	char* srcPathExtention;
	strcpy(desPath, srcPath);
	getFileExtention(desPath, &srcPathExtention);
	char* ptrString;
	char* changeExtention;
	ptrString = strstr(srcPath, "rmy");
	if (ptrString)
	changeExtention = strtok(srcPathExtention, "rmy");
	else
	{
		strcpy(desPath, srcPath);
		strcat(desPath, "rmy");
	}
	printf("des %s\n", desPath);
	printf("src %s\n", srcPath);
}
void createLogFile() {
	time_t rawtime;
	time(&rawtime);
	char logPath[MAX_PATH_LEN];
	sprintf(logPath, "Logs\\log_SA_TEST_%s.txt", ctime(&rawtime));
	// Lets convert space to _ in
	char* p = logPath;
	for (; *p; ++p)
	{
		if (*p == ' ' || *p == '\n')
			*p = '_';
		else if (*p == ':')
			*p = '-';
	}
	logFd = openLogFile(logPath, "w");
}
void writeToLog(char* massage) {
	if (logFd != NULL)
		writeDataToLog(logFd, massage);
}
void closeLog() {
	if (logFd != NULL)
		closeFile(logFd);
}
char* getTime(){
	time_t     now;
	struct tm* ts;
	/* Get the current time */
	now = time(NULL);

	ts = localtime(&now);
	strftime(time_buf, sizeof(time_buf), "%H:%M:%S", ts);
	return time_buf;
}

//Note that this function must be done immediatly after open file (before start reads or writes)
//because it moves the seek to the begining of file
long getFileSize(FILE* fd)
{
	fseek(fd, 0, SEEK_END); //move to 0 bytes to the end
	long fileSize = ftell(fd); //get the size (pos at end)
	rewind(fd); //same as fseek(file,0,SEEK_SET), move the position to the begining
	return fileSize;
}
