#include "structs.h"

void init_tables (tables *tables) {	
	tables->table_1 = (record*)malloc(sizeof(record) * NUM_OF_LINES_IN_FILE_1);
	tables->table_2 = (record*)malloc(sizeof(record) * NUM_OF_LINES_IN_FILE_2);
}

void init_buffer (buffer *buffer) {
	buffer->next = NULL;
}

buffer *new_buffer (buffer *old) {
	buffer *new = malloc(sizeof(buffer));
	old->next = new;
	return new;
}

void destroy_buffers (buffer *buffers) {
	buffer *temp;
	buffer *next;
	for (temp=buffers; temp; temp=next) {
		next = temp->next;
		free(temp);
		if (next == NULL)
			break;
	}
}

void fill_bin_table (tables *tables) {
	int i = 0;
	int j = 0;
	uint64_t temp = 0;
	uint64_t compare = 255;
	
	for (i=0; i<NUM_OF_LINES_IN_FILE_1; i++) {
		temp = tables->table_1[i].key;
		tables->table_1[i].bin[0] = temp & compare;
		for (j=1; j<8; j++) {
			temp = temp>>8;
			tables->table_1[i].bin[j] = temp & compare;
		}
	}
	for (i=0; i<NUM_OF_LINES_IN_FILE_2; i++) {
		temp = tables->table_2[i].key;
		tables->table_2[i].bin[0] = temp & compare;
		for (j=1; j<8; j++) {
			temp = temp>>8;
			tables->table_2[i].bin[j] = temp & compare;
		}
	}
}

void sort (record *unsorted_table, record *sorted_table, int position, int records, int byte) {
// Variables
	int i = 0;
	int j = 0;
	int x = 0;
	int z = 0;
	int k = 0;
	histogram *hist = malloc(sizeof(histogram)*256);;
	for (j=0; j<256; j++) {
		hist[j].value = 0;
		hist[j].temp_table = (record*)malloc(sizeof(record) * MAX_NUM_OF_RECORDS_IN_TEMP_SORTED_TABLE);
	}
	int psum[256];
	for (j=0; j<256; j++) {
		psum[j] = 0;
	}
// Algorithm
	for (j=0; j<256; j++) {
		for (i=0; i<records; i++) {
			if (unsorted_table[i].bin[byte] - j == 0) {
				hist[j].temp_table[hist[j].value] = unsorted_table[i];
				hist[j].temp_table[hist[j].value].rowID = i;
				hist[j].value++;
			}
		}
	}
	i = 0;
	for (j=0; j<256; j++) {
		psum[j] = i;
		i = i + hist[j].value;
	}
	for (j=0; j<256; j++) {
		if (hist[j].value != 0 && byte == 0) {
			z = 0;
			k = psum[j]+position;
			k = k + hist[j].value;
			for (x=psum[j]+position; x<k; x++) {
				sorted_table[x] = hist[j].temp_table[z];
				z++;
			}
		} else if (hist[j].value <= MAX_NUM_FOR_QUICKSORT && hist[j].value != 0) {
			quicksort(hist[j].temp_table, 0, hist[j].value - 1);
			z = 0;
			k = psum[j]+position;
			k = k + hist[j].value;
			for (x=psum[j]+position; x<k; x++) {
				sorted_table[x] = hist[j].temp_table[z];
				z++;
			}
		} else if (hist[j].value > MAX_NUM_FOR_QUICKSORT) {
			sort(hist[j].temp_table, sorted_table, psum[j]+position, hist[j].value, byte-1);
		}
	}
	for (j=0; j<256; j++) {
		free(hist[j].temp_table);
	}
	free(hist);
}

void quicksort (record *unsorted_table, int first, int last) {
// Variables
	int i = 0;
	int j = 0;
	int pivot = 0;
	uint64_t temp = 0;
// Algorithm
	if (first<last) {
    	pivot = first;
    	i = first;
    	j = last;
		while (i<j) {
			while (unsorted_table[i].key<=unsorted_table[pivot].key && i<last)
				i++;
			while (unsorted_table[j].key>unsorted_table[pivot].key)
				j--;
			if (i<j) {
				temp = unsorted_table[i].key;
				unsorted_table[i].key = unsorted_table[j].key;
				unsorted_table[j].key = temp;
			}
		}
		temp=unsorted_table[pivot].key;
		unsorted_table[pivot].key=unsorted_table[j].key;
		unsorted_table[j].key=temp;
		quicksort(unsorted_table,first,j-1);
		quicksort(unsorted_table,j+1,last);
	}
}

void merge (buffer *buffer, tables *sorted_tables, tables *unsorted_tables) {
// Variables
	int position_1 = 0;
	int position_2 = 0;
	int position_2_first = 0;
	int position_2_last = 0;
	int i = 0;
	uint64_t prev = -1;
	int total = 0;
// Algorithm
	for (position_1=0; position_1<NUM_OF_LINES_IN_FILE_1; position_1++) {
		for (position_2=position_2_first; position_2<=position_2_last; position_2++) {
			if (sorted_tables->table_1[position_1].key > sorted_tables->table_2[position_2].key) {
				if (position_2_last < NUM_OF_LINES_IN_FILE_2 - 1) {
					position_2 = position_2_last;												//	 GAMW TO SPITI MOU!
					position_2_last++;
					position_2_first = position_2_last;
				}
			} else if (sorted_tables->table_1[position_1].key < sorted_tables->table_2[position_2].key) {
				break;
			} else if (sorted_tables->table_1[position_1].key == sorted_tables->table_2[position_2].key) {
				if (i == 41666) {
					buffer = new_buffer(buffer);
					init_buffer(buffer);
					i = 0;
				}
				buffer->table[i].key = sorted_tables->table_1[position_1].key;
				buffer->table[i].payload_A = unsorted_tables->table_1[sorted_tables->table_1[position_1].rowID].payload;
				buffer->table[i].payload_B = unsorted_tables->table_2[sorted_tables->table_2[position_2].rowID].payload;
				i++;
				total++;
				if (sorted_tables->table_1[position_1].key != prev) {
					if (position_2_last < NUM_OF_LINES_IN_FILE_2 - 1) {
						if (sorted_tables->table_2[position_2].key == sorted_tables->table_2[position_2 + 1].key) {
							position_2_last++;
						}
					}
				}
			}
		}
		prev = sorted_tables->table_1[position_1].key;
	}
	buffer->table[i].key = -1;
	printf("*****	Result = %9d	*****\n", total);
}
