#include <stdio.h> 
#include <stdlib.h>

#define _GNU_SOURCE
#include <getopt.h>

static void do_head(FILE* f, int nlines);

#define DEFAULT_N_LINES 10

static struct option longopts[] = {
	{"lines", required_argument, NULL, 'n'},
	{"help", no_argument, NULL, 'h'},
	{0, 0, 0, 0}
};

int main(int argc, char* argv[])
{
	int opt;
	long nlines = DEFAULT_N_LINES;

	while((opt = getopt_long(argc, argv, "hn:", longopts, NULL)) != -1) {
		switch (opt) {
			case 'n': 
				nlines = atol(optarg);
				break;
			case 'h':
				fprintf(stdout, "(help)Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
				exit(0);
			default:
				fprintf(stderr, "(error)Usage: %s [-n LINES] [FILE ...]\n", argv[0]);
				exit(1);
		}
	}

	if (optind == argc) {
		do_head(stdin, nlines);
	} else {
		int i;

		for (i = optind; i < argc; i++) {
			FILE *f;
			f = fopen(argv[i], "r");
			if (!f) {
				perror (argv[i]);
				fclose(f);
			}
			do_head(f, nlines);
			fclose(f);
		}
	}
	return 0;
}

static void do_head(FILE* f, int nlines) 
{
	int c;
	if (nlines <= 0) return;
	while((c = fgetc(f)) != EOF) {
		if (fputc(c, stdout) < 0) exit(1);  
		if (c == '\n') {
			nlines--;
			if (nlines == 0)  return;
		}
	}
}
