#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static int do_wc_l(const char *path);
static void die(const char *s);

int main(int argc, char *argv[]){
	int i;
	if (argc < 2) {
		fprintf(stderr, "%s: file name not given\n", argv[0]);
		exit(1);
	}
	for (i = 1; i < argc; i++) {
		printf("%s: %d\n", argv[i], do_wc_l(argv[i]));
	}
	exit(0);
}

#define BUFFER_SIZE 1 

static int do_wc_l(const char *path)
{
	int ret, fd;
	unsigned char buf[BUFFER_SIZE];
	int n;

	fd = open(path, O_RDONLY);
	if (fd < 0) die(path);
	ret = 0;
	for (;;) {
		n = read(fd, buf, sizeof(buf));
		if (n < 0) die(path);
		if (n == 0) break;
		if (buf[0] == '\n') ret++;
	}
	if (close(fd) < 0) die(path);
	return ret;
}	

static void die(const char* s)
{
	perror(s);
	exit(1);
}
	
