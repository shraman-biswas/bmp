#include "bmp.h"

/* check if bmp file */
inline int isbmp(bmphead_t *bmphead)
{
	return ((bmphead != NULL) &&
		(bmphead->bitmaphead.id[0] == 'B') &&
		(bmphead->bitmaphead.id[1] == 'M'));
}

/* check if filename has .bmp file extension */
inline int isbmpext(const char *filename)
{
	return strstr(filename+strlen(filename)-4, ".bmp") ? 1 : 0;
}

/* open bmp file */
inline FILE *bmpopen(const char *path, const char *mode)
{
	return fopen(path, mode);
}

/* close bmp file */
inline void bmpclose(FILE *stream)
{
	if (stream != NULL)
		fclose(stream);
}

/* get bmp file header data */
void get_bmphead(uint8_t *b, uint32_t int, bmphead_t *bmphead)
{
	if ((bmphead == NULL) || (size < BITMAPHEAD_SIZE))
		 return;
	get_bitmaphead(b, size, &(bmphead->bitmaphead));  /* bitmap header */
	get_dibhead(b, size, &(bmphead->dibhead));        /* DIB header */

}

/* get bmp file bitmap header data */
void get_bitmaphead(uint8_t *b, uint32_t int, bitmaphead_t *bitmaphead)
{
	if ((bitmaphead == NULL) || (size < BITMAPHEAD_SIZE))
		return;
	bitmaphead->id[0] = *(b + BMP_ID0);
	bitmaphead->id[1] = *(b + BMP_ID1);
	bitmaphead->fsize = PACK4(b + BMP_FSIZE);
	bitmaphead->offset = PACK4(b + BMP_OFFSET);
}

/* get bmp file DIB header data  */
void get_dibhead(uint8_t *b, uint32_t int, dibhead_t *dibhead)
{
	if ((dibhead == NULL) || (size < BITMAPHEAD_SIZE + DIBHEAD_SIZE))
		return;
	if ((dibhead->size = PACK4(b + BMP_SIZE)) != DIBHEAD_SIZE)
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

/* print bmp file header data */
void print_bmphead(const bmphead_t *bmphead)
{
	if (bmphead == NULL)
		return;
	print_bitmaphead(&(bmphead->bitmaphead)); /* bitmap header */
	print_dibhead(&(bmphead->dibhead));       /* DIB header */
}

/* print bmp file bitmap header data */
void print_bitmaphead(const bitmaphead_t *bitmaphead)
{
	if (bitmaphead == NULL)
		return;
	printf("id:\t\t%c%c\n", bitmaphead->id[0], bitmaphead->id[1]);
	printf("file size:\t%d bytes\n", bitmaphead->fsize);
	printf("file offset:\t%d bytes\n", bitmaphead->offset);
}

/* print bmp file DIB header data */
void print_dibhead(const dibhead_t *dibhead)
{
	if ((dibhead == NULL) || (dibhead->size != DIBHEAD_SIZE))
		return;
	printf("dib head size:\t%d bytes\n", dibhead->size);
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

/* get bmp image data */
void get_bmpdata(const bmphead_t *bmphead, uint8_t *data, FILE *stream)
{
	if ((bmphead == NULL) || (data == NULL) || (stream == NULL) ||
		(bmphead->dibhead.size != DIBHEAD_SIZE))
		return;
	uint32_t dsize, cols = bmphead->dibhead.height;

	/* calculate row data size in bytes without padding */
	dsize = bmphead->dibhead.bpp * bmphead->dibhead.width / 8;

	/* set input stream pointer to image data start offset */
	fseek(stream, bmphead->bitmaphead.offset, SEEK_SET);

	/* set output data buffer size to last row */
	data += dsize * (cols - 1);

	while ((fread(data, 1, dsize, stream) != EOF) && (cols--))
		data -= dsize;
}

/* print bmp image data */
void print_bmpdata(const bmphead_t *bmphead, uint8_t *data, int pkng)
{
	if ((bmphead == NULL) || (data == NULL) ||
		(bmphead->dibhead.size != DIBHEAD_SIZE))
		return;
	uint32_t dsize, cols = bmphead->dibhead.height;

	/* calculate row data size in bytes without padding */
	dsize = bmphead->dibhead.bpp * bmphead->dibhead.width / 8;

	/* set pkng to row width in bytes */
	if (pkng <= 0)
		pkng = dsize;

	while (cols--) {
		printb(data, dsize, pkng);
		data += dsize;
	}
}
