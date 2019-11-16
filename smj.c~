#include "smj.h"

int main(int argc, char **argv) {
// Random Variables
	int i = 0;
	int error = 0;
	int check = 0;
	char input_file_name_1[FILENAME_MAX_LENGTH];
	char input_file_name_2[FILENAME_MAX_LENGTH];
// Database Variables
	unsorted_tables *Unsorted_tables = malloc(sizeof(unsorted_tables));
	sorted_tables *Sorted_tables = malloc(sizeof(sorted_tables));
	init_unsorted_tables (Unsorted_tables);
	init_sorted_tables (Sorted_tables);
	buffer *root = malloc(sizeof(buffer));
	init_buffer (root);
// Arguments
	printf("*****	Checking Arguments	*****\n");
    for (i=0; i<4; i++) {
    	if (strcmp(argv[i], "-1") == 0) {
    		strcpy(input_file_name_1, argv[i+1]);
    		check++;
    	}
        if (strcmp(argv[i], "-2") == 0) {
    		strcpy(input_file_name_2, argv[i+1]);
    		check++;
    	}	
    }
    if (check != 2) {
    	printf("*****	Wrong Arguments	*****\nPlease rerun : ./smj -1 <inputfilename> -2 <inputfilename>\n");
    	exit(1);
    }
    printf("*****	Arguments checked	*****\n");
// Reading the tables from the files
	printf("*****	Opening input files	*****\n");
	parse_input_file(Unsorted_tables, input_file_name_1, input_file_name_2);
	printf("*****	Closing input files	*****\n");
//	printf("*****	Unsorted table 1	*****\n");
//	print_unsorted_table (Unsorted_tables->table_1, NUM_OF_LINES_IN_FILE_1);
//	printf("*****	Unsorted table 2	*****\n");
//	print_unsorted_table (Unsorted_tables->table_2, NUM_OF_LINES_IN_FILE_2);
// Creating binary tables
	printf("*****	Creating bin tables	*****\n");
	fill_bin_table(Unsorted_tables);
// Sorting tables
	printf("*****	Sorting table 1 	*****\n");
	sort (Unsorted_tables->table_1, Sorted_tables->table_1, 0, NUM_OF_LINES_IN_FILE_1, 7);
//	printf("*****	Sorted table 1		*****\n");
//	print_sorted_table (Sorted_tables->table_1, NUM_OF_LINES_IN_FILE_1);
	printf("*****	Sorting table 2 	*****\n");
	sort (Unsorted_tables->table_2, Sorted_tables->table_2, 0, NUM_OF_LINES_IN_FILE_2, 7);
//	printf("*****	Sorted table 2		*****\n");
//	print_sorted_table (Sorted_tables->table_2, NUM_OF_LINES_IN_FILE_2);
// Merging tables
	printf("*****	Merging tables		*****\n");
	merge (root, Sorted_tables, Unsorted_tables);
//	printf("*****	Merged table		*****\n");
//	print_merged_table (root); 
// Deleting everything - Shutdown
	printf("*****	Shuting Down smj	*****\n");
	destroy_buffers (root);
	free(Unsorted_tables->table_1);
	free(Unsorted_tables->table_2);
	free(Unsorted_tables);
	free(Sorted_tables->table_1);
	free(Sorted_tables->table_2);
	free(Sorted_tables);
	return 0;
}
