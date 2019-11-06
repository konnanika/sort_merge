#include "merged.h"
// Initialize the buffer
void init_buffer (buffer *buffer) {
	buffer->next = NULL;
}
// Create a new buffer
buffer *new_buffer (buffer *old) {
	buffer *new = malloc(sizeof(buffer));
	old->next = new;
	return new;
}
// Destroy all the buffers
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
// Merge 2 sorted tables and save the records to the buffer list
void merge (buffer *buffer, sorted_tables *sorted_tables, unsorted_tables *unsorted_tables) {
// Variables
	int position_1 = 0;
	int position_2 = 0;
	int position_2_first = 0;
	int position_2_last = 0;
	int i = 0;
	uint64_t prev = -1;
	int total = 0;
// Read 1 record from the sorted table 1 from start to finish
	for (position_1=0; position_1<NUM_OF_LINES_IN_FILE_1; position_1++) {
	// Read 1 record from the sorted table 2 from first to last
		for (position_2=position_2_first; position_2<=position_2_last; position_2++) {
		// If the record from table 1 is higher from the record from table 2
			if (sorted_tables->table_1[position_1].key > sorted_tables->table_2[position_2].key) {
			// Read the next of last in table 2
				if (position_2_last < NUM_OF_LINES_IN_FILE_2 - 1) {
					position_2 = position_2_last;
					position_2_last++;
					position_2_first = position_2_last;
				}
		// If the record from table 1 is lower from the record from table 2
			} else if (sorted_tables->table_1[position_1].key < sorted_tables->table_2[position_2].key) {
			// Read the next in table 1
				break;
		// If the record from table 1 is equal to the record from table 2
			} else if (sorted_tables->table_1[position_1].key == sorted_tables->table_2[position_2].key) {
			// If you need to create new buffer, create it
				if (i == SIZE_OF_THE_BUFFER) {
					buffer = new_buffer(buffer);
					init_buffer(buffer);
					i = 0;
				}
			// Insert the record to the buffer
				buffer->table[i].key = sorted_tables->table_1[position_1].key;
				buffer->table[i].payload_A = unsorted_tables->table_1[sorted_tables->table_1[position_1].rowID].payload;
				buffer->table[i].payload_B = unsorted_tables->table_2[sorted_tables->table_2[position_2].rowID].payload;
				i++;
				total++;
			// If there is a previous record in table 1
				if (sorted_tables->table_1[position_1].key != prev) {
				// If the table 2 is not finished
					if (position_2_last < NUM_OF_LINES_IN_FILE_2 - 1) {
					// If the next in table 2 is equal to the one we compare at the moment
						if (sorted_tables->table_2[position_2].key == sorted_tables->table_2[position_2 + 1].key) {
						// Move the last to the next record
							position_2_last++;
						}
					}
				}
			}
		}
	// Keep the key of the record from table 1 so it can be used during the next read
		prev = sorted_tables->table_1[position_1].key;
	}
// When its all done add a mark to define the end of the records
	buffer->table[i].key = -1;
	printf("*****	Result = %9d	*****\n", total);
}
// Print merged table
void print_merged_table (buffer *buffer) {
	int i = 0;
	printf("\n*****************************************************************************************************************\n");
	printf("***********	key	******************	payload_A	******************	payload_A	*********\n");
	printf("*****************************************************************************************************************\n");
	while (buffer) {
		for (i=0; i<SIZE_OF_THE_BUFFER; i++) {
			if (buffer->table[i].key == -1)
				break;
			printf("*%29" PRIu64 "	*	%29" PRIu64 "	*	%29" PRIu64 "	*\n", buffer->table[i].key, buffer->table[i].payload_A, buffer->table[i].payload_B);
		}
		buffer = buffer->next;
	}
	printf("*****************************************************************************************************************\n\n");
}
