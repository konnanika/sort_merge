#include "sorted.h"
// Initialize the 2 sorted tables
void init_sorted_tables (sorted_tables *sorted_tables) {	
	sorted_tables->table_1 = (sorted_record*)malloc(sizeof(sorted_record) * NUM_OF_LINES_IN_FILE_1);
	sorted_tables->table_2 = (sorted_record*)malloc(sizeof(sorted_record) * NUM_OF_LINES_IN_FILE_2);
}
// Initialize the histogram
void init_histogram (histogram *hist) {
	int j = 0;
	for (j=0; j<256; j++) {
		hist[j].value = 0;
		hist[j].temp_table = (unsorted_record*)malloc(sizeof(unsorted_record) * MAX_NUM_OF_RECORDS_IN_TEMP_SORTED_TABLE);
	}
}
// Initialize the psum
void init_psum (int psum[256]) {
	int j = 0;
	for (j=0; j<256; j++) {
		psum[j] = 0;
	}
}
// Read an unsorted table and sort them in the same table recursively
void sort (unsorted_record *unsorted_table, sorted_record *sorted_table, int position, int records, int byte) {
// Variables
	int i = 0;
	int j = 0;
	int x = 0;
	int z = 0;
	int current_position = 0;
// Temporary Database Variables
	histogram *hist = malloc(sizeof(histogram)*256);;
	init_histogram (hist);
	int psum[256];
	init_psum (psum);
// Read the unsorted table and fill the histogram
	for (j=0; j<256; j++) {
		for (i=0; i<records; i++) {
			if (unsorted_table[i].bin[byte] - j == 0) {
				hist[j].temp_table[hist[j].value] = unsorted_table[i];
				hist[j].value++;
			}
		}
	}
// Fill the psum
	i = 0;
	for (j=0; j<256; j++) {
		psum[j] = i;
		i = i + hist[j].value;
	}
// Read the unsorted table in 1 position of the histogram
	for (j=0; j<256; j++) {
	// Insert the records to the sorted table if checking the last byte
		if (hist[j].value != 0 && byte == 0) {
			z = 0;
			current_position = psum[j]+position + hist[j].value;
			for (x=psum[j]+position; x<current_position; x++) {
				sorted_table[x].key = hist[j].temp_table[z].key;
				sorted_table[x].rowID = hist[j].temp_table[z].rowID;
				z++;
			}
	// Run quicksort it is possible and insert the records to the sorted table
		} else if (hist[j].value <= MAX_NUM_FOR_QUICKSORT && hist[j].value != 0) {
			quicksort(hist[j].temp_table, 0, hist[j].value - 1);
			z = 0;
			current_position = psum[j]+position + hist[j].value;
			for (x=psum[j]+position; x<current_position; x++) {
				sorted_table[x].key = hist[j].temp_table[z].key;
				sorted_table[x].rowID = hist[j].temp_table[z].rowID;
				z++;
			}
	// Run sort recursively if quicksort is not possible
		} else if (hist[j].value > MAX_NUM_FOR_QUICKSORT) {
			sort(hist[j].temp_table, sorted_table, psum[j]+position, hist[j].value, byte-1);
		}
	}
// Destroy the histogram
	for (j=0; j<256; j++) {
		free(hist[j].temp_table);
	}
	free(hist);
}
// Read an unsorted table and sort them in the same table recursively
void quicksort (unsorted_record *unsorted_table, int first, int last) {
// Variables
	int i = 0;
	int j = 0;
	int pivot = 0;
	unsorted_record temp;
// Quicksort with pivot the first record
	if (first<last) {
    	pivot = first;
    	i = first;
    	j = last;
    // Read the table from first and from last as long as its not the same record
		while (i<j) {
		// Read first to last and stop if you find a record with higher key than the pivot
			while (unsorted_table[i].key<=unsorted_table[pivot].key && i<last)
				i++;
		// Read last to first and stop if you find a record with lower or equal key than the pivot
			while (unsorted_table[j].key>unsorted_table[pivot].key)
				j--;
		// If the records i and j are not in the right place
			if (i<j) {
			// Swap them
				temp = unsorted_table[i];
				unsorted_table[i] = unsorted_table[j];
				unsorted_table[j] = temp;
			}
		}
	// Swap j with pivot
		temp = unsorted_table[pivot];
		unsorted_table[pivot] = unsorted_table[j];
		unsorted_table[j] = temp;
	// Run quicksort recursively 1 time for each subtable
		quicksort(unsorted_table,first,j-1);
		quicksort(unsorted_table,j+1,last);
	}
}
// Print an sorted table
void print_sorted_table (sorted_record *table, int records) {
	int i = 0;
	printf("\n*************************************************************************\n");
	printf("counter ***********	key	******************	rowID	*********\n");
	printf("*************************************************************************\n");
	for (i=0; i<records; i++)
		printf("%d	*%29" PRIu64 "	*	%20d	*\n", i, table[i].key, table[i].rowID);
	printf("*************************************************************************\n\n");
}
