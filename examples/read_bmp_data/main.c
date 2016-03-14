#include "main.h"

int main(int argc, char **argv)
{
	printf("[ read bmp data ]\n");

	char *filename, path[PATH_LEN] = "../../images/";
	uint8_t data[480*640*3], raw[BYTES]={0};
	size_t len;
	FILE *fp;
	bmphead_t bmphead;

	/* get image filename */
	filename = (argc > 1) ? argv[1] : "test.bmp";
	if (!isbmpext(filename)) {
		fprintf(stderr, "not a bmp file!\n");
		exit(EXIT_FAILURE);
	}

	/* create path name from filename */
	len = strlen(filename);
	if (PATH_LEN <= (strlen(path) + len)) {
		fprintf(stderr, "bmp filename is too long (%ld chars)!\n", len);
		exit(EXIT_FAILURE);
	}
	strncat(path, filename, len);

	/* bmp file handling */
	fp = bmpopen(path, "rb");				/* open bmp file */
	if (fread(raw, 1, BYTES, fp) == EOF) {	/* read raw data */
		fprintf(stderr, "bmp file header bytes not be read!\n");
		exit(EXIT_FAILURE);
	}
	get_bmphead(raw, BYTES, &bmphead);		/* parse bmp file header */
	get_bmpdata(&bmphead, data, fp);		/* read bmp data */
	print_bmpdata(&bmphead, data, PKNG);	/* print bmp data */
	bmpclose(fp);							/* close bmp file */

	return EXIT_SUCCESS;
}
