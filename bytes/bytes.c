#include "bytes.h"

void fgetb(uint8_t *s, uint32_t size, FILE *stream)
{
	if (!stream) {
		fprintf(stderr, "stream is null!\n");
		return;
	}
	while (((*s++ = fgetc(stream)) != EOF) && (size--));
}

void printb(uint8_t *s, uint32_t size, int pkng)
{
	while (size)
		printf("%02x%s", *s++, --size % pkng ? " " : "\n");
}