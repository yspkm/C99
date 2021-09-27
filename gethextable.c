#include <stdio.h>

char hex[] = "0123456789ABCDEF";
unsigned char byte[8+1]; 
FILE* file = NULL;

void getByte(unsigned char byte[], int num)
{
	for (int i = 7; i >= 0; i--) {
		byte[i] = num % 0x2 + '0'; 
		num /= 0x2;
	}
	byte[8] = '\0';
}

void printHorLine(int row)
{
	for (int i = 0; i < 137; i++) {
		fprintf(file, "-");
	}

	if (row >= 0 && row < 16) {
		fprintf(file, "\n%c(", hex[row]);
		getByte(byte, row);
		for(int i = 4; i < 8; i++) {
			fprintf(file, "%c", byte[i]);
		}
		fprintf(file, ")| ");
	} else {
		fprintf(file, "\n");
	}
}

void printHorTwoLine(int row)
{
	for (int i = 0; i < 137; i++) {
		fprintf(file, "=");
	}
	if (row >= 0 && row < 16) {
		fprintf(file, "\n%c(", hex[row]);
		getByte(byte, row);
		for(int i = 4; i < 8; i++) {
			fprintf(file, "%c", byte[i]);
		}
		fprintf(file, ")| ");
	}
}

int main(void) 
{
	int row = 0;
	int j = 0, jj=0;	
	file = fopen("hextable.txt", "w");

	fprintf(file, "         ");
	for (int i = 0; i < 16; i++) {
		getByte(byte, i);
		fprintf(file, "|%c(", hex[i]);
		for (int j = 4; j < 8; j++) {
			fprintf(file, "%c", byte[j]);
		}
		fprintf(file, ")");
	}
	fprintf(file, "\n");
	printHorTwoLine(0);
	//printHorLine(0);
	for (int i = 0; i < 256; i++) {
		char u = hex[i % 0x10];
		char l = hex[(i / 0x10) % 0x10];

		fprintf(file, "|%c%c(%03d)", u, l, i);
		j++;	
		if (j == 16) {
			fprintf(file, "\n");
			j = 0;
			row++;
			printHorLine(row);
		}
	}
	fprintf(file, "\n");

	return 0;
}
