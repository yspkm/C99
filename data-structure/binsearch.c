#include "myheader.h" // p.14

int binsearch(int sorted_list[], int searchnum, int left, int right)
{ /*search list[0] <= list[1] <= ... <= list[n-1] for search num, Return its position if found. Otherwise return -1*/
	int middle;
	while(left <= right) {
		middle = (left + right)/2;
		switch (COMPARE(sorted_list[middle], searchnum)) {
			case -1	: left = middle + 1; break;
			case 0	: return middle;
			case 1	: right = middle - 1;
		}
	}
	return -1;
}