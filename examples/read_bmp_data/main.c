#include "main.h"

int main(int argc, char **argv)
{
	printf("[ read bmp data ]\n");

	char *filename, path[PATH_LEN] = "../../images/";
	uint8_t data[480*640*3], raw[BYTES]={0};
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

	/* read raw header data */
	if (fread(raw, 1, BYTES, fp) == EOF) {
		fprintf(stderr, "bmp file header bytes not be read!\n");
		exit(EXIT_FAILURE);
	}

	/* parse bmp file header */
	get_bmphead(raw, BYTES, &bmphead);

	/* check if bmp file in bmp header */
	if (!isbmp(&bmphead)) {
		fprintf(stderr, "not a bmp file!\n");
		exit(EXIT_FAILURE);
	}

	/* read bmp data */
	get_bmpdata(&bmphead, data, fp);

	/* print bmp data */
	print_bmpdata(&bmphead, data, PKNG);

	/* close bmp file */
	bmpclose(fp);

	return EXIT_SUCCESS;
}
