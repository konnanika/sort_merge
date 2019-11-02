#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {

	int i = 0;
	int64_t table[24];

	for (i=0; i<25; i++)
		table[i] = i;

	for (i=0; i<25; i++)
		printf("Table[%d] = %ld\n", i, table[i]);
	return 0;
}


