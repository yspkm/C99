#ifndef MYHEADER
#define MYHEADER

#include <stdio.h>
#include <stdlib.h>

#define MALLOC(p,s) if(!((p)=malloc(s))) {fprintf(stderr,"Insufficient memory");exit(EXIT_FAILURE);}
#define SWAP(x,y,t) ((t) = (x), (x) = (y), (y) = (t)) // e.g. int a=1; int b=2; int temp; swap(a, b, temp);
#define COMPARE(x,y) (((x) < (y)) ? -1 : ((x) == (y)) ? 0 : 1)

#endif
