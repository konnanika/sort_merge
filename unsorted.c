#include "unsorted.h"
// Initialize the 2 unsorted tables
void init_unsorted_tables (unsorted_tables *unsorted_tables) {	
	unsorted_tables->table_1 = (unsorted_record*)malloc(sizeof(unsorted_record) * NUM_OF_LINES_IN_FILE_1);
	unsorted_tables->table_2 = (unsorted_record*)malloc(sizeof(unsorted_record) * NUM_OF_LINES_IN_FILE_2);
}
// Fill, for each unsorted_record, a table (size of 8 bytes)
// where each element has the unsigned value of each byte
void fill_bin_table (unsorted_tables *tables) {
// Variables
	int i = 0;
	int j = 0;
	uint64_t temp = 0;
	uint64_t compare = 255;
// Fill bin tables in records from file 1
	for (i=0; i<NUM_OF_LINES_IN_FILE_1; i++) {
		temp = tables->table_1[i].key;
		tables->table_1[i].bin[0] = temp & compare;
		for (j=1; j<8; j++) {
			temp = temp>>8;
			tables->table_1[i].bin[j] = temp & compare;
		}
	}
// Fill bin tables in records from file 2
	for (i=0; i<NUM_OF_LINES_IN_FILE_2; i++) {
		temp = tables->table_2[i].key;
		tables->table_2[i].bin[0] = temp & compare;
		for (j=1; j<8; j++) {
			temp = temp>>8;
			tables->table_2[i].bin[j] = temp & compare;
		}
	}
}
// Print an unsorted table
void print_unsorted_table (unsorted_record *table, int records) {
	int i = 0;
	printf("\n*****************************************************************************************************************\n");
	printf("counter ***********	key	******************	payload_A	******************	rowID	*********\n");
	printf("*****************************************************************************************************************\n");
	for (i=0; i<records; i++)
		printf("%d	*%29" PRIu64 "	*	%29" PRIu64 "	*	%20d	*\n", i, table[i].key, table[i].payload, table[i].rowID);
	printf("*****************************************************************************************************************\n\n");
}
