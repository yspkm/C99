#include <errno.h>

{
	errno = 0; // first of all, set errno as 0
	if (fputs(buf, f) == EOF) { // if it reaches end of file
		if (errno != 0)  { // check whether errno was changed or not
			/* print error message according to errno 
			 * /
		}
	}
}
			
