#include <stdio.h>

void printHorLine(FILE* file, int row, char* hex, char* hor)
{
	for (int i = 0; i < 67; i++) {
		fprintf(file, "%s", hor);
	}

	if (row >= 0 && row < 16) {
		fprintf(file, "\n%c*", hex[row]);
		fprintf(file, " ");
	} else {
		fprintf(file, "\n");
	}
}

int main(void) 
{
	int row = 0;
	int j = 0, jj=0;	
	char *hex = "0123456789ABCDEF";
	FILE* file = fopen("hextable.txt", "w");

	fprintf(file, "<BIN-HEX-DEC QUICK REFERENCE TABLE>\n");

	fprintf(file, "(b:h:d) 1010:A:10|1011:B:11|1100:C:12");
	fprintf(file, "|1101:D:13|1110:E:14|1111:F:15\n");

	fprintf(file, "   ");
	for (int i = 0; i < 16; i++) {
		fprintf(file, "| *%c", hex[i]);
	}
	fprintf(file, "\n");

	printHorLine(file, 0, hex, "=");
	for (int i = 0; i < 256; i++) {
		fprintf(file, "|%03d", i);
		j++;	
		if (j == 16) {
			fprintf(file, "\n");
			j = 0;
			row++;
			if (i < 255) {
				printHorLine(file, row, hex, "-");
			} 
		}
	}

	return 0;
}
