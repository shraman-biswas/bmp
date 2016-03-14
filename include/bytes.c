#include "bytes.h"

/* get byte buffer of specified size from specified file stream */
void fgetb(uint8_t *bytes, int size, FILE *stream)
{
	if (!stream) {
		fprintf(stderr, "stream is null!\n");
		return;
	}
	while (((*bytes++ = fgetc(stream)) != EOF) && (size--));
}

/* print byte buffer of specified size with specified byte packing width */
void printb(uint8_t *bytes, int size, int pkng)
{
	while (size)
		printf("%02x%c", *bytes++, --size % pkng ? ' ' : '\n');
}
