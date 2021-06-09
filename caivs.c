#include <ctype.h>
#include <err.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static int pflag;
static int sflag;
static int zflag;

static void caivs(void);

int
main(int argc, char **argv)
{
	int c;

	while ((c = getopt(argc, argv, "psz")) != -1) {
		switch (c) {
		case 'p':
			pflag = 1;
			break;
		case 's':
			sflag = 1;
			break;
		case 'z':
			zflag = 1;
			break;
		default:
			err(1, "getopt");
			break;
		}
	}
	caivs();
}

/* caivs: toy program to "romanize" text.
 * Makes "Gaius Julius Caesar" into "CAIVS IVLIVS CAESAR"
 */
static void
caivs(void)
{
	int c;

	for (;;) {
		c = getchar();
		if (c == EOF) {
			if (ferror(stdin))
				err(1, "getchar");
			if (feof(stdin))
				exit(0);
		}
		if (pflag && ispunct(c))
			continue;
		if (sflag && isspace(c))
			continue;

		c = toupper(c);
		switch(c) {
		case 'G':
			c = 'C';
			break;
		case 'J':
			c = 'I';
			break;
		case 'U':
			c = 'V';
			break;
		case 'W':
			c = 'V';
			errno = 0;
			/* Print an extra 'V'. */
			if (putchar(c) == EOF && errno)
				err(1, "putchar");
			break;
		}
		if (zflag) {
			switch(c) {
			case 'Y':
				c = 'I';
				break;
			case 'Z':
				c = 'S';
				break;
			}
		}

		errno = 0;
		if (putchar(c) == EOF && errno)
			err(1, "putchar");
	}
}
