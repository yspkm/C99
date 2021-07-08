#include <stdio.h> 
#include <stdlib.h>

static void do_head(FILE* f, int nlines);

int main(int argc, char* argv[])
{
	long nlines;

	if (argc < 2) {
		fprintf(stdout, "Usage: %s n [file file ...]\n", argv[0]);
		exit(1);
	}
	nlines = atol(argv[1]); // stdlib.h
	if (argc == 2) { //do_head from FILE* stdin in stdio.h
		do_head(stdin, nlines);
	} else { 
		int i; //iteration variable

		for (i = 2; i < argc; i++) {
			FILE *f; 

			f = fopen(argv[i], "r");
			if (!f) {
				perror(argv[i]);
				exit(1);
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
		if (fputc(c, stdout) < 0) exit(1); // error 
		if (c == '\n') {
			nlines--;
			if (nlines == 0)  return;
		}
	}
}
