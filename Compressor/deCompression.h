#include "utities.h"
#include "fileOperaitionAPI.h"

#define DICT_SIZE	(1 << 20)
#define VALUE_NULL	DICT_SIZE
#define HASH_SIZE	(DICT_SIZE)

typedef struct bit_buf {
	unsigned long buf;  //bif
	unsigned num;     //number of bit
}bit_buf;

typedef struct node_dec
{
	int prev;		        // prefix code
	unsigned char ch;		// last symbol
}
node_dec;

// LZW decoder context
typedef struct _lzw_dec
{
	int            code;			// current code
	unsigned       max;				// maximal code
	unsigned       codesize;		// number of bits in code
	bit_buf        bitBuf;		    // bit-buffer struct
	void*          stream;	        // pointer to the stream object
	unsigned       lzwn;			// input code-buffer byte counter
	unsigned       lzwm;			// input code-buffer size
	unsigned char* inbuff;		    // input code-buffer
	node_dec       dict[DICT_SIZE];	// code dictionary
	unsigned char  c;				// first char of the code
	unsigned char buff[DICT_SIZE];	// output string buffer
}
lzw_dec_t;

char* deCompression();
void deCompress();
