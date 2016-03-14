#include "bytes.h"

/* print byte buffer of specified size with specified byte packing width */
void printb(uint8_t *bytes, int size, int pkng)
{
	while (size)
		printf("%02x%c", *bytes++, --size % pkng ? ' ' : '\n');
}
