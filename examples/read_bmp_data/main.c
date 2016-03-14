#include "main.h"

int main(int argc, char **argv)
{
	printf("[ read bmp data ]\n");

	char *filename, path[PATH_LEN] = "../../images/";
	uint8_t raw[BYTES]={0};
	size_t len;
	FILE *fp;
	_bmphead_t bmphead;

	/* get image filename */
	filename = (argc > 1) ? argv[1] : "test.bmp";
	if (!isbmp(filename)) {
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

	/* open bmp file */
	fp = bmpopen(path, "rb");

	/* read raw data */
	fgetb(raw, BYTES, fp);

	/* parse bmp file header */
	get_bmphead(raw, BYTES, &bmphead);

	/* read bmp data */

	/* close bmp file */
	bmpclose(fp);

	return EXIT_SUCCESS;
}
