#ifndef BMP_H
#define BMP_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "bytes.h"

/* bitmap header size */
#define BITMAPHEAD_SIZE	14

/* DIB header size */
#define DIBHEAD_SIZE	40

/* bitmap header offsets */
#define BMP_ID0		0x0
#define BMP_ID1		0x1
#define BMP_FSIZE	0x2
#define BMP_OFFSET	0xa

/* DIB header offsets */
#define BMP_SIZE	0xe
#define BMP_WIDTH	0x12
#define BMP_HEIGHT	0x16
#define BMP_CLRPL	0X1a
#define BMP_BPP		0x1c
#define BMP_COMP	0x1e
#define BMP_ISIZE	0x22
#define BMP_XRES	0x26
#define BMP_YRES	0x2a
#define BMP_NCLR	0x2e
#define BMP_IMPCLR	0x32

/* pack 2 bytes from little-endian to big-endian */
#define PACK2(x) ((*(x)) | (*((x)+1) << 8))

/* pack 4 bytes from little-endian to big-endian */
#define PACK4(x) \
	((*(x)) | (*((x)+1) << 8) | (*((x)+2) << 16) | (*((x)+3) << 32))

/* bitmap header structure */
typedef struct __bitmaphead_t {
	uint32_t fsize, offset;
	uint8_t id[2];
} bitmaphead_t;

/* DIB header structure */
typedef struct __dibhead_t {
	uint32_t size, width, height, comp, isize, xres, yres, nclr, impclr;
	uint16_t clrpl, bpp;
} dibhead_t;

/* bmp file header structure */
typedef struct __bmphead_t {
	bitmaphead_t bitmaphead;
	dibhead_t dibhead;
} bmphead_t;

inline int isbmp(bmphead_t *bmphead);
inline int isbmpext(const char *filename);
inline FILE *bmpopen(const char *path, const char *mode);
inline void bmpclose(FILE *stream);
void get_bmphead(uint8_t *b, int size, bmphead_t *bmphead);
void get_bitmaphead(uint8_t *b, int size, bitmaphead_t *bitmaphead);
void get_dibhead(uint8_t *b, int size, dibhead_t *dibhead);
void print_bmphead(const bmphead_t *bmphead);
void print_bitmaphead(const bitmaphead_t *bitmaphead);
void print_dibhead(const dibhead_t *dibhead);
void get_bmpdata(const bmphead_t *bmphead, uint8_t *data, FILE *stream);
void print_bmpdata(const bmphead_t *bmphead, uint8_t *data, int pkng);

#endif
