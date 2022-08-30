#include "lzw.h"

#pragma warning(disable:4996)
#define __STDC_WANT_LIB_EXT1__ 1
#define _GNU_SOURCE 
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#define WIN32_LEAN_AND_MEAN
//#define debug_version 2
//#define EXIT_FAILURE 1

/******************************************************************************
**  lzw_hash
**  --------------------------------------------------------------------------
**  Hash function is used for searching of <prefix>+<symbol> combination
**  in the hash table.
**z
**  Arguments:
**      value - prefix value;
**      ch    - symbol;
**
**  Return: Hash code
******************************************************************************/
__inline static int lzw_hash(const int value, const unsigned char c)
{
	return (value ^ ((int)c << 6)) & (HASH_SIZE - 1);
}
/******************************************************************************
**  lzw_enc_writebits
**  --------------------------------------------------------------------------
**  Write bits into bit-buffer.
**  The number of bits should not exceed 24.
**
**  Arguments:
**      ctx     - pointer to LZW context;
**      bits    - bits to write;//=str from func enc
**      nbits   - number of bits to write, 0-24;//=codesize
**
**  Return: -
******************************************************************************/
//static void lzw_enc_writebits(lzw_enc* const ctx, unsigned value, unsigned valuesize) {
//	// shift old bits to the left, add new to the right
//	ctx->bitBuf.buf = (ctx->bitBuf.buf << valuesize) | (value & ((1 << valuesize) - 1));
//
//	valuesize += ctx->bitBuf.num;
//
//	while (valuesize >= 8) {
//		valuesize -= 8;
//		//12345678987654321//
//		//1/ value -size=size of value +ctx.bitbuf.num
//		//value=12345678 ctx.bitbuf.num=0 -> valuesize=8
//		//value=123456789 ctx.bitbuf.num=1 -> valuesize=10
//		//exe= valuesize-8=1  123456789 >> 1 12345678 buff[1]=12345678 
//		ctx->buff[ctx->indexBuf++] = ctx->bitBuf.buf >> valuesize;
//		//this code - if ctx->indexBuf==256
//		//if finish size in arr buf 
//		if (ctx->indexBuf == sizeof(ctx->buff)) {
//			ctx->indexBuf = 0;
//			//writeDataToFile(ctx->buff, 1, sizeof(ctx->buff), ctx->outputFile);
//			lzw_writebuf(ctx->outputFile, ctx->buff, sizeof(ctx->buff));
//			//fwrite(ctx->buff, sizeof(ctx->buff), 1, ctx->outputFile);
//		}
//	}
//	ctx->bitBuf.num = valuesize;
//}

static void lzw_enc_writebits(lzwEnc* const ctx, unsigned bits, unsigned nbits)
{
	// shift old bits to the left, add new to the right
	ctx->bitBuf.buf = (ctx->bitBuf.buf << nbits) | (bits & ((1 << nbits) - 1));

	nbits += ctx->bitBuf.num;

	// flush whole bytes
	while (nbits >= 8)
	{
		nbits -= 8;
		ctx->buff[ctx->indexBuf++] = ctx->bitBuf.buf >> nbits;

		if (ctx->indexBuf == sizeof(ctx->buff)) {
			ctx->indexBuf = 0;
			lzw_writebuf(ctx->outputFile, ctx->buff, sizeof(ctx->buff));
		}
	}

	ctx->bitBuf.num = nbits;
}


/******************************************************************************
**  lzw_enc_init
**  --------------------------------------------------------------------------
**  Initializes LZW encoder context.
**
**  Arguments:
**      ctx     - LZW context;
**      stream  - Pointer to Input/Output stream object;
**
**  Return: -
******************************************************************************/
void lzw_enc_init(lzwEnc* ctx, void* outputFile) {

	ctx->value = VALUE_NULL;  //non-existent value
	ctx->indexMax = 255;      //all chars signal 
	ctx->outputFile = outputFile;
	ctx->valuesize = 8;
	ctx->bitBuf.num = 0;
	ctx->indexBuf = 0;

	unsigned i;//equal unsigned int i

	//clear hash table
	for (i = 0; i < HASH_SIZE; i++)
		ctx->hash[i] = VALUE_NULL;

	for (i = 0; i < 256; i++) {
		int code_hash = lzw_hash(VALUE_NULL, i);//get code index from function hash

		ctx->dict[i].prev = VALUE_NULL;//non-existent value berfore signal char
		ctx->dict[i].next = ctx->hash[code_hash];
		ctx->dict[i].c = i;//current value
		ctx->hash[code_hash] = i;
	}
}

/******************************************************************************
**  lzw_enc_reset
**  --------------------------------------------------------------------------
**  Reset LZW encoder context. Used when the dictionary overflows.
**  Code size set to 8 bit.
**
**  Arguments:
**      ctx     - LZW encoder context;
**
**  Return: -
******************************************************************************/
static void lzw_enc_reset(lzwEnc* const ctx) {

	ctx->indexMax = 255;
	ctx->valuesize = 8;
	unsigned i;
	for (i = 0; i < HASH_SIZE; i++)
		ctx->hash[i] = VALUE_NULL;

	for (i = 0; i < 256; i++)
	{
		int hash = lzw_hash(VALUE_NULL, i);
		//TODO
		ctx->dict[i].next = ctx->hash[hash];
		ctx->hash[hash] = i;
	}
}
/******************************************************************************
**  lzw_enc_findstr
**  --------------------------------------------------------------------------
**  Searches a string in LZW dictionaly. It is used only in encoder.
**  Fast search is performed by using hash table.
**  Full search is performed by using embedded linked lists.
**
**  Arguments:
**      ctx  - LZW context;
**      code - code for the string beginning (already in dictionary);
**      c    - last symbol;
**
**  Return: code representing the string or CODE_NULL.
******************************************************************************/

static int lzw_enc_findstr(lzwEnc* const ctx, int value, unsigned char c)
{
	int i;
	//search hash
	//get index of dict from hash
	//in dict go all iteration to next
	//next=ctx->hash[code_hash] for before code
	for (i = ctx->hash[lzw_hash(value, c)]; i != VALUE_NULL; i = ctx->dict[i].next)
	{
		//if value in dict and c in dict (value is begining str and c is end of str) 
		if (ctx->dict[i].prev == value && ctx->dict[i].c == c) {
			break;
		}
	}
	return i;
}

/******************************************************************************
**  lzw_enc_addstr
**  --------------------------------------------------------------------------
**  Adds string to the LZW dictionaly.
**
**  Arguments:
**      ctx  - LZW context;
**      value - vlue for the string beginning (already in dictionary);
**      c    - last symbol;
**
**  Return: index representing the string in dict or CODE_NULL if dictionary is full.
******************************************************************************/
static int lzw_enc_addstr(lzwEnc* ctx, int value, unsigned char c)
{

	if (++ctx->indexMax == DICT_SIZE) {
		//ofter that I am representing the state to init the dict
		printf("ERROR");
		return -1;
	}
	int code_hash = lzw_hash(value, c);

	// add new code
	ctx->dict[ctx->indexMax].prev = value;//begining str
	ctx->dict[ctx->indexMax].c = c;       //end str
	ctx->dict[ctx->indexMax].next = ctx->hash[code_hash];//The link list go back all value connect to prev value
	ctx->hash[code_hash] = ctx->indexMax;//put index in hash

	return ctx->indexMax;//return index to dict
}

/******************************************************************************
**  lzw_encode
**  --------------------------------------------------------------------------
**  Encode buffer by LZW algorithm. The output data is written by application
**  specific callback to the application defined stream inside this function.
**
**  Arguments:
**      ctx  - LZW encoder context;
**      buf  - input byte buffer;
**      size - size of the buffer;
**
**  Return: Number of processed bytes.
******************************************************************************/

int lzw_encode(lzwEnc* ctx, char buf[], unsigned size) {

	if (!size)
		return 0;//size==0

	unsigned i;
	for (i = 0; i < size; i++) {
		unsigned char c = buf[i];
		int nextChar = lzw_enc_findstr(ctx, ctx->value, c);
		
		if (nextChar == VALUE_NULL) {
			//-write prefix
			lzw_enc_writebits(ctx, ctx->value, ctx->valuesize);
#ifdef debug_version
			printf("%d", ctx->value);
			printf("\n");
#endif
			// increase the code size (number of bits) if needed
			if (ctx->indexMax + 1 == (1 << ctx->valuesize))
				ctx->valuesize++;
			// add <prefix>+<current symbol> to the dictionary
			if (lzw_enc_addstr(ctx, ctx->value, c) == VALUE_NULL)
			{
				// dictionary is full - reset encoder
				lzw_enc_reset(ctx);
			}
			ctx->value = c;
		}
		else
		{
			//nextChar=<prefix>+<current symbol>
			ctx->value = nextChar;
		}
	}
	
	return size;
}

void lzw_enc_end(lzwEnc* ctx)
{
#if DEBUG
	printf("code %x (%d)\n", ctx->code, ctx->codesize);
#endif
	// write last code
	lzw_enc_writebits(ctx, ctx->value, ctx->valuesize);
	// flush bits in the bit-buffer
	if (ctx->bitBuf.num)
		lzw_enc_writebits(ctx, 0, 8 - ctx->bitBuf.num);
	lzw_writebuf(ctx->outputFile, ctx->buff, ctx->indexBuf);
}
lzwEnc lzw;
void compressionProcess() {
	char srcFileName[MAX_PATH_LEN];
	getPathToBuffer(srcFileName, "Enter file path to compress:");
	FILE* srcFd = openFile(srcFileName, "rb");
	char* outFileName = "out.txt";
	FILE* outFd = openFile(outFileName, "w+b");
	lzwEnc* ctx = &lzw;
	char bufferInProgress[SIZE_BUF];
	lzw_enc_init(ctx, outFd);
	unsigned len;
	while (len = lzw_readbuf(srcFd, bufferInProgress, sizeof(bufferInProgress)))
	{
		lzw_encode(ctx, bufferInProgress, len);
	}

	lzw_enc_end(ctx);
	closeFile(srcFd);
	closeFile(outFd);
}