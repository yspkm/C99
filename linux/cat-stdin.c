#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

static void do_cat(const char *path, char std_fd);
static void die(const char *s);

int main(int argc, char *argv[]){
	int i;
	if (argc < 2) {
		//fprintf(stderr, "%s: file name not given\n", argv[0]);
		do_cat("stdin", 1);	
		exit(1);
	}
	for (i = 1; i < argc; i++) {
		do_cat(argv[i], 0);
	}
	exit(0);
}

#define BUFFER_SIZE 2048

static void do_cat(const char *path, char std_fd)
{
	int fd;
	unsigned char buf[BUFFER_SIZE];
	int n;
	
	if (std_fd) {
		fd = STDIN_FILENO;
	} else {
		fd = open(path, O_RDONLY);
	}

	if (fd < 0) die(path);
	for (;;) {
		n = read(fd, buf, sizeof(buf));
		if (n < 0) die(path);
		if (n == 0) break;
		if (write(STDOUT_FILENO, buf, n) < 0) die(path);
	}
	if (close(fd) < 0) die(path);
}	

static void die(const char* s)
{
	perror(s);
	exit(1);
}
	
