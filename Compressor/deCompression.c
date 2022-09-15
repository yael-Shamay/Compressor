#include "lzw.h"
#include "utities.h"

/******************************************************************************
** lzw_dec_readbits
** --------------------------------------------------------------------------
** Read bits from bit - buffer.
* *The number of bits should not exceed 24.
* *
**Arguments:
**ctx - pointer to LZW context;
**nbits - number of bits to read, 0 - 24;
**
**Return: bits or -1 if there is no data
******************************************************************************/

static int lzwDecReadbits(lzwDec *const ctx, unsigned codesize) {
	//read bits
	while (ctx->bitBuf.num < codesize) {//need more bits
		if (ctx->countbuf == ctx->sizebuf)
			return -1;
		// shift old bits to the left, add new to the right
		ctx->bitBuf.buf = (ctx->bitBuf.buf << 8) | (ctx->inbuff[ctx->countbuf++]);
		ctx->bitBuf.num += 8;
	}
	//ctx->bitBuf.num equal to the size of the unread bits
	ctx->bitBuf.num -= codesize;
	//puts the required bits at the end and returns them by a mask
	return (ctx->bitBuf.buf >> ctx->bitBuf.num)& ((1 << codesize) - 1);
}

/******************************************************************************
**  lzw_dec_init
**  --------------------------------------------------------------------------
**  Initializes LZW decoder context.
**
**  Arguments:
**      ctx     - LZW decoder context;
**      stream  - Pointer to application defined Input/Output stream object;
**
**  Return: -
******************************************************************************/
void lzwDecInit(lzwDec *ctx, void *file)
{
	unsigned i;

	ctx->code = VALUE_NULL;
	ctx->max = 255;
	ctx->codesize = 8;
	ctx->bitBuf.num = 0; // bitbuffer init
	ctx->outputFile = file;

	for (i = 0; i < 256; i++)
	{
		ctx->dict[i].prev = VALUE_NULL;
		ctx->dict[i].ch = i;
	}
}

static void lzwDecReset(lzwDec *const ctx) {
	ctx->codesize = 8;
	ctx->max = 255;
	ctx->code = VALUE_NULL;
}
/******************************************************************************
**  lzw_dec_getstr
**  --------------------------------------------------------------------------
**  Reads string from the LZW dictionaly. Because of particular dictionaty
**  structure the buffer is filled from the end so the offset from the
**  beginning of the buffer will be <buffer size> - <string size>.
**
**  Arguments:
**      ctx  - LZW context;
**      code - code of the string (already in dictionary);
**
**  Return: the number of bytes in the string
******************************************************************************/
static unsigned lzwDecGetstr(lzwDec *const ctx, int code) {
	unsigned i = sizeof(ctx->buff);
	while (code != VALUE_NULL && i) {
		ctx->buff[--i] = ctx->dict[code].ch;
		code = ctx->dict[code].prev;
	}
	return sizeof(ctx->buff) - i;
}

/******************************************************************************
**  lzw_dec_addstr
**  --------------------------------------------------------------------------
**  Adds string to the LZW dictionaly.
**
**  Arguments:
**      ctx  - LZW context;
**      code - code for the string beginning (already in dictionary);
**      c    - last symbol;
**
**  Return: code representing the string or CODE_NULL if dictionary is full.
******************************************************************************/

static int lzwDecAddstr(lzwDec *const ctx, int code, unsigned char c) {
	//c already in dict
 	if (code == VALUE_NULL)
		return c;
	// dict is full
	if (++ctx->max == VALUE_NULL)
		return VALUE_NULL;
	//put <code>+<c> in dict
	ctx->dict[ctx->max].ch = c;
	ctx->dict[ctx->max].prev = code;

	return ctx->max;
}

/******************************************************************************
**  lzw_dec_writestr
**  --------------------------------------------------------------------------
**  Writes a string represented by the code into output stream.
**  The code should always be in the dictionary.
**  It is important that codesize is increased after code is sent into
**  output stream.
**
**  Arguments:
**      ctx  - LZW context;
**      code - LZW code;
**
**  Return: The first symbol of the output string.
******************************************************************************/

static unsigned char lzwDecWritestr(lzwDec* const ctx, int code) {
	// get string for the new code from dict
	unsigned strlen = lzwDecGetstr(ctx, code);
	// write the string into the output file
	lzwWritebuf(ctx->outputFile, ctx->buff+(sizeof(ctx->buff) - strlen), strlen);
	// to remember the first sybmol of this string
	return ctx->buff[sizeof(ctx->buff) - strlen];
}


/******************************************************************************
**  lzw_decode
**  --------------------------------------------------------------------------
**  Decodes buffer of LZW codes and writes strings into output stream.
**  The output data is written by application specific callback to
**  the application defined stream inside this function.
**
**  Arguments:
**      ctx  - LZW context;
**      buf  - input code buffer;
**      size - size of the buffer;
**
**  Return: Number of processed bytes or error code if the value is negative.
******************************************************************************/

int lzwDe(lzwDec* const ctx, char buf[], unsigned size) {
	if (!size)return 0;

	ctx->inbuff = buf;
	ctx->countbuf = 0;
	ctx->sizebuf = size;

	for (;;) {
		int nextcode;
		// read a code from the input buffer (ctx->inbuff[])
		nextcode = lzwDecReadbits(ctx, ctx->codesize);
		if (nextcode < 0) {
			break;
		}
		else if (nextcode <= ctx->max)//known code 
		{
			// output string for the new code from dictionary
			ctx->c = lzwDecWritestr(ctx, nextcode);
			// add <prev code str>+<first str symbol> to the dictionary
			if (lzwDecAddstr(ctx, ctx->code, ctx->c) == VALUE_NULL)
				return LZW_ERR_DICT_IS_FULL;
		}
		else {
			// unknown code
			// try to guess the code
			if (nextcode != ctx->max + 1)
				return LZW_ERR_WRONG_CODE;

			// create code: <nc> = <code> + <c> wich is equal to ncode
			if (lzwDecAddstr(ctx, ctx->code, ctx->c) == VALUE_NULL)
				return LZW_ERR_DICT_IS_FULL;

			// output string for the new code from dict
			ctx->c = lzwDecWritestr(ctx, nextcode);
		}
		ctx->code = nextcode;
		// increase the code size (number of bits) if needed
		if (ctx->max + 1 >= (1 << ctx->codesize))
			ctx->codesize++;

		// check the dictionary overflow
		if (ctx->max+1 == DICT_SIZE)
			lzwDecReset(ctx);

	}
	return ctx->countbuf;
}
lzwDec lzw;
void deCompression() {
	writeToLog("compressionProcess function\n");
	char srcFileName[MAX_PATH_LEN];
	char outFileName[MAX_PATH_LEN];
	getPathToBuffer(srcFileName, "Enter file path to Decompress:");
	createPathToInputFile(srcFileName, outFileName);
	decompressProcces(srcFileName, outFileName);
}

void decompressProcces(char* compressedFile, char* outFile)
{
	sprintf(massage, "compress:\nsrc file path to deCompress: %s\n deCompress file path : %s\n", compressedFile, outFile);
	writeToLog(massage);
	FILE* srcFd = openFile(compressedFile, "rb");
	writeToLog("open src file success\n");
	FILE* outFd = openFile(outFile, "w+b");
	writeToLog("create output file success\n");
	if (getFileSize(srcFd) == 0) {
		writeToLog("src is empty file\n");
		printf("src is empty file\ndo exit\n");
		closeFile(srcFd);
		exit(-1);
	}

	writeToLog("deCompressing...\n");

	sprintf(massage, "src file size before deCompress: %ld\n", getFileSize(srcFd));
	writeToLog(massage);
	lzwDec* ctx = &lzw;
	char bufferInProgress[SIZE_BUF];
	unsigned   len;
	lzwDecInit(ctx, outFd);

	while (len = lzwReadbuf(srcFd, bufferInProgress, sizeof(bufferInProgress)))
	{
		int ret = lzwDe(ctx, bufferInProgress, len);

		if (ret != len)
		{
			fprintf(stderr, "Error %d\n", ret);
			break;
		}
	}
	writeToLog("end deCompress success\n");
	sprintf(massage, "out file size after deCompress: %ld\n", getFileSize(outFd));
	writeToLog(massage);
	fclose(outFd);
	fclose(srcFd);
	writeToLog("close files success\n");
}
