#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "utities.h"
#include "fileOperaitionAPI.h"

#pragma once
#define DICT_SIZE	(1 << 20)
#define HASH_SIZE  DICT_SIZE
#define BUFF_SIZE  10
#define VALUE_NULL	(DICT_SIZE)
#define SIZE_BUF 256

#define LZW_ERR_DICT_IS_FULL	-1
#define LZW_ERR_INPUT_BUF		-2
#define LZW_ERR_WRONG_CODE		-3

typedef struct bitBuf {
	unsigned long buf;  //bif
	unsigned num;     //number of bit
}bitBuf;

typedef struct node_enc
{
	int           prev;		// prefix code
	int           next;		// next child code
	unsigned char c;		// current char
}
node_enc;

typedef struct nodeDec
{
	int prev;		        // prefix code
	unsigned char ch;		// last symbol
}
nodeDec;


typedef struct lzwEnc
{
	int value;                       // current value 
	unsigned  indexMax;              // maximal space in hash
	node_enc dict[DICT_SIZE];	     // code dictionary
	int hash[HASH_SIZE];	         // hast table
	void* outputFile;	             // pointer to the stream object
	int valuesize;                   // count bit of write
	unsigned indexBuf;		     	 // output code-buffer byte counter
	bitBuf   bitBuf;				 // bit-buffer struct, holds the output bits
	unsigned char buff[BUFF_SIZE];   // output bits buffer
}lzwEnc;

typedef struct lzwDec
{
	int           code;				// current code
	unsigned      max;				// maximal code
	unsigned      codesize;			// number of bits in code
	bitBuf        bitBuf;			  	// bit-buffer struct
	void*         outputFile;	    // pointer to the stream object
	unsigned      countbuf;				// input code-buffer byte counter
	unsigned      sizebuf;				// input code-buffer size
	unsigned char* inbuff;		    // input code-buffer
	nodeDec    dict[DICT_SIZE];	    // code dictionary
	unsigned char c;				// first char of the code
	unsigned char buff[DICT_SIZE];	// output string buffer
}
lzwDec;

void compressionProcess();
void deCompression();
void compressFile(char* fileToCompress, char* outFileName);
void decompressProcces(char* compressedFile, char* outFile);

//void compression(lzwEnc lzw);

void lzw_enc_init(lzwEnc* ctx, void* outputFile);//init hash
int  lzw_encode(lzwEnc* ctx, char buf[], unsigned size);
void lzw_enc_end(lzwEnc* ctx);

void lzwDecInit(lzwDec* ctx, void* file);
int lzwDe(lzwDec* const ctx, char buf[], unsigned size);


void lzwWritebuf(void* outFile, char* buf, unsigned size);
unsigned lzwReadbuf(void* outFile, char* buf, unsigned size);

void lzw_writebuf(void* stream, char* buf, unsigned size);
unsigned lzw_readbuf(void* stream, char* buf, unsigned size);
