#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "utities.h"
"file_operaitions_API.h"
#pragma once
#include <stdio.h>
#define DICT_SIZE	(1 << 20)
#define HASH_SIZE  DICT_SIZE
#define BUFF_SIZE  10
#define VALUE_NULL	(DICT_SIZE)
#define SIZE_BUF 256

typedef struct bit_buf {
	unsigned long buf;  //bif
	unsigned num;     //number of bit
}bit_buf;

typedef struct node_enc
{
	int           prev;		// prefix code
	int           next;		// next child code
	unsigned char c;		// current char
}
node_enc;

typedef struct lzw_enc
{
	int value;                       // current value 
	unsigned  indexMax;              // maximal space in hash
	node_enc dict[DICT_SIZE];	     // code dictionary
	int hash[HASH_SIZE];	         // hast table
	void* outputFile;	             // pointer to the stream object
	int valuesize;                   // count bit of write
	unsigned indexBuf;		     	 // output code-buffer byte counter
	bit_buf   bitBuf;				 // bit-buffer struct, holds the output bits
	unsigned char buff[BUFF_SIZE];   // output bits buffer
}lzw_enc;

//void compressionProcess();
void theCompression();

void lzw_enc_init(lzw_enc* ctx, void* outputFile);//init hash
int  lzw_encode(lzw_enc* ctx, char buf[], unsigned size);
void lzw_enc_end(lzw_enc* ctx);


void lzw_writebuf(void* stream, char* buf, unsigned size);
unsigned lzw_readbuf(void* stream, char* buf, unsigned size);
char* compression();