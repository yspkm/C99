#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 2048

int main(int argc, char* argv[]) 
{
	int i;
	char buf[BUFSIZE];	

	for (i = 1; i < argc; i++) {
		FILE* f; 
		int num;
		
		f = fopen(argv[i], "r");

		do {
			num = fread(buf, sizeof(char), BUFSIZE, f);
			if (fwrite(buf, num, sizeof(char), stdout) != num) exit(1);
		} while(num == BUFSIZE-1);
		fclose(f);
	}

	return 0;
}
