#include "bmp.h"

FILE *bmpopen(const char *path, const char *mode)
{
	return fopen(path, mode);
}

int bmpclose(FILE *stream)
{
	if (stream) {
		fclose(stream);
		return 0;
	} else {
		return -1;
	}
}

void get_bmphead(uint8_t *b, uint32_t size, _bmphead_t *bmphead)
{
	if ((size < BITMAPHEAD_SZ) || (!bmphead)) /* min 14 bytes required */
		 return;
	get_bitmaphead(b, size, &(bmphead->bitmaphead)); /* bitmap file header */
	get_dibhead(b, size, &(bmphead->dibhead)); /* DIB header */

}

void get_bitmaphead(uint8_t *b, uint32_t size, _bitmaphead_t *bitmaphead)
{
	bitmaphead->id[0] = *(b + BMP_ID0);
	bitmaphead->id[1] = *(b + BMP_ID1);
	bitmaphead->fsize = PACK4(b + BMP_FSIZE);
	bitmaphead->offset = PACK4(b + BMP_OFFSET);	
}

void get_dibhead(uint8_t *b, uint32_t size, _dibhead_t *dibhead)
{
	dibhead->size = PACK4(b + BMP_SIZE);
	if ((dibhead->size != DIBHEAD_SZ) && (size < (BITMAPHEAD_SZ + DIBHEAD_SZ))) /* BITMAPINFOEADER */
		return;
	dibhead->width = PACK4(b + BMP_WIDTH);
	dibhead->height = PACK4(b + BMP_HEIGHT);
	dibhead->clrpl = PACK2(b + BMP_CLRPL);
	dibhead->bpp = PACK2(b + BMP_BPP);
	dibhead->comp = PACK4(b + BMP_COMP);
	dibhead->isize = PACK4(b + BMP_ISIZE);
	dibhead->xres = PACK4(b + BMP_XRES);
	dibhead->yres = PACK4(b + BMP_YRES);
	dibhead->nclr = PACK4(b + BMP_NCLR);
	dibhead->impclr = PACK4(b + BMP_IMPCLR);
}

void print_bmphead(const _bmphead_t *bmphead)
{
	if (!bmphead)
		return;
	print_bitmaphead(&(bmphead->bitmaphead)); /* bitmap file header */
	print_dibhead(&(bmphead->dibhead)); /* DIB header */
}

void print_bitmaphead(const _bitmaphead_t *bitmaphead)
{
	printf("id: %c%c\n", bitmaphead->id[0], bitmaphead->id[1]);
	printf("file size:\t%d bytes\n", bitmaphead->fsize);
	printf("file offset:\t%d bytes\n", bitmaphead->offset);
}

void print_dibhead(const _dibhead_t *dibhead)
{
	printf("dib head size:\t%d bytes\n", dibhead->size);
	if (dibhead->size != 40) /* BITMAPINFOEADER */
		return;
	printf("image width:\t%d pixels\n", dibhead->width);
	printf("image height:\t%d pixels\n", dibhead->height);
	printf("colour planes:\t%d\n", dibhead->clrpl);
	printf("bits per pixel:\t%d bits\n", dibhead->bpp);
	printf("compression:\t%d\n", dibhead->comp);
	printf("image size:\t%d bytes\n", dibhead->isize);
	printf("X resolution:\t%d ppm\n", dibhead->xres);
	printf("Y resolution:\t%d ppm\n", dibhead->yres);
	printf("colours:\t%d\n", dibhead->nclr);
	printf("imp. colours:\t%d\n", dibhead->impclr);
}