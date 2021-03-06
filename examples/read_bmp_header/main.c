#include "main.h"

int main(int argc, char **argv)
{
	printf("[ read bmp header ]\n");

	char *filename, path[PATH_LEN] = "../../images/";
	uint8_t raw[BYTES];
	size_t len;
	FILE *fp=NULL;
	bmphead_t bmphead;

	/* get image filename */
	filename = (argc > 1) ? argv[1] : "test.bmp";
	if (!isbmpext(filename)) {
		fprintf(stderr, "not a .bmp file!\n");
		exit(EXIT_FAILURE);
	}

	/* create path name from filename */
	len = strlen(filename);
	if (PATH_LEN <= (strlen(path) + len)) {
		fprintf(stderr, "bmp filename is too long (%ld chars)!\n", len);
		exit(EXIT_FAILURE);
	}
	strncat(path, filename, len);

	/* open bmp file */
	fp = bmpopen(path, "rb");

	/* read raw data */
	if (fread(raw, 1, BYTES, fp) == EOF) {
		fprintf(stderr, "bmp file header bytes not be read!\n");
		exit(EXIT_FAILURE);
	}
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
