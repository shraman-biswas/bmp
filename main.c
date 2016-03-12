#include "main.h"

int main(void)
{
	printf("[ read bmp file ]\n");

	uint8_t raw[BYTES]={0};
	FILE *fp;
	_bmphead_t bmphead;

	/* open bmp file */
	fp = bmpopen("images/test.bmp", "rb");

	/* read raw data */
	fgetb(raw, BYTES, fp);
	printb(raw, BYTES, PKNG);

	/* parse bmp file header */
	get_bmphead(raw, BYTES, &bmphead);
	print_bmphead(&bmphead);

	/* close bmp file */
	bmpclose(fp);

	return EXIT_SUCCESS;
}
