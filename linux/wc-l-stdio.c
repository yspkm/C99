#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) 
{
	int i;
	for (i = 1; i < argc; i++) {
		FILE *f;
		int c, cnt;

		f = fopen(argv[i], "r");
		if (!f) {
			perror(argv[i]);
			exit(1);
		}
		cnt = 0;
		while((c = fgetc(f)) != EOF) {
			if (c == '\n') cnt++;
		}
		printf("%d %s\n", cnt, argv[i]);
		fclose(f);
	}

	return 0;
}
