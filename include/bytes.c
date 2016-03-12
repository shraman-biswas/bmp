#include "bytes.h"

/* gets byte buffer of specified size from specified file stream */
void fgetb(uint8_t *s, uint32_t size, FILE *stream)
{
	if (!stream) {
		fprintf(stderr, "stream is null!\n");
		return;
	}
	while (((*s++ = fgetc(stream)) != EOF) && (size--));
}

/* prints byte buffer of specified size with specified byte packing width */
void printb(uint8_t *s, uint32_t size, int pkng)
{
	while (size)
		printf("%02x%c", *s++, --size % pkng ? ' ' : '\n');
}
