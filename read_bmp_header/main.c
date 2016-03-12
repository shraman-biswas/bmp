#include "main.h"

int main(int argc, char **argv)
{
	printf("[ read bmp header ]\n");

	char *filename, path[80] = "../images/";
	uint8_t raw[BYTES]={0};
	size_t len;
	FILE *fp;
	_bmphead_t bmphead;

	/* get image filename */
	filename = (argc > 1) ? argv[1] : "test.bmp";
	if (!isbmp(filename)) {
		fprintf("not a bmp file!\ns");
		exit(EXIT_FAILURE);
	}

	/* create path name from filename */
	len = strlen(filename);
	len = (80 - strlen(path) - len) ? len : 80 - strlen(path);
	strncat(path, filename, len);

	/* open bmp file */
	fp = bmpopen(path, "rb");
	/* read raw data */
	fgetb(raw, BYTES, fp);
	printf("raw data:\n");
	printb(raw, BYTES, PKNG);

	/* parse bmp file header */
	get_bmphead(raw, BYTES, &bmphead);
	printf("\nbmp header data:\n");
	print_bmphead(&bmphead);

	/* close bmp file */
	bmpclose(fp);

	return EXIT_SUCCESS;
}
