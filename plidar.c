#include <err.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void	pushBuf(int c);
static void	usage(void);

static void
pushBuf(int c)
{
	static char buf[10] = "";

	for (int i = 0; i < 8; i++)
		buf[i+0] = buf[i+1];
	buf[8] = c;
	putchar(buf[4]);
	if (strcmp(buf, "\x20\x6D\x3F\x0D\x0A\x1B\x0C\x0D\x0A") == 0)
		usleep(100000);
}

int
main(int argc, char *argv[])
{
	FILE *fp;
	int c;

	if (argc != 2)
		usage();

	fp = fopen(argv[1], "r");
	if (fp == NULL)
		err(1, "%s", argv[1]);

	while ((c = getc(fp)) != EOF)
		pushBuf(c);
	(void)fclose(fp);
	for (int i = 0; i < 4; i++)
		pushBuf(0);

	return 0;
}

static void
usage(void)
{
	fprintf(stderr, "usage: plidar file\n");
	exit(1);
}
