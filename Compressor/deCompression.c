#include "deCompression.h"

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
void lzw_dec_init(lzw_dec_t* ctx, void* stream)
{
	unsigned i;

	ctx->code = VALUE_NULL;
	ctx->max = 255;
	ctx->codesize = 8;
	ctx->bitBuf.num = 0; // bitbuffer init
	ctx->stream = stream;

	for (i = 0; i < 256; i++)
	{
		ctx->dict[i].prev = VALUE_NULL;
		ctx->dict[i].ch = i;
	}
}










char* deCompression() {

}
void deCompress() {

}
