#include "smj.h"

int main(int argc, char **argv) {
// Random Variables
	int i = 0;
	int error = 0;
	int check = 0;
	char input_file_name_1[FILENAME_MAX_LENGTH];
	char input_file_name_2[FILENAME_MAX_LENGTH];
// Database Variables
	tables *official_tables = malloc(sizeof(tables));
	tables *sorted_tables = malloc(sizeof(tables));
	init_tables (official_tables);
	init_tables (sorted_tables);
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
	parse_input_file(official_tables, input_file_name_1, input_file_name_2);
	printf("*****	Closing input files	*****\n");
//	printf("	**********	key	******************	payload_A	*******\n");
//	for (i=0; i<NUM_OF_LINES_IN_FILE_1; i++)
//		printf("%d	*%29" PRIu64 "	*	%29" PRIu64 "	*\n", i, official_tables->table_1[i].key, official_tables->table_1[i].payload);
//	sleep(5);
//	for (i=0; i<NUM_OF_LINES_IN_FILE_2; i++)
//		printf("%d	*%29" PRIu64 "	*	%29" PRIu64 "	*\n", i, official_tables->table_2[i].key, official_tables->table_2[i].payload);
//	sleep(5);
// Creating binary tables
	printf("*****	Creating bin tables	*****\n");
	fill_bin_table(official_tables);
// Sorting tables
	printf("*****	Sorting table 1 	*****\n");
	sort (official_tables->table_1, sorted_tables->table_1, 0, NUM_OF_LINES_IN_FILE_1, 7);
//	sleep(5);
//	printf("	**********	key	******************	payload_A	*******\n");
//	for (i=0; i<NUM_OF_LINES_IN_FILE_1; i++)
//		printf("%d	*%29" PRIu64 "	*	%29" PRIu64 "	*\n", i, sorted_tables->table_1[i].key, sorted_tables->table_1[i].payload);
//	sleep(5);
	printf("*****	Sorting table 2 	*****\n");
	sort (official_tables->table_2, sorted_tables->table_2, 0, NUM_OF_LINES_IN_FILE_2, 7);
//	sleep(5);
//	printf("	**********	key	******************	payload_A	*******\n");
//	for (i=0; i<NUM_OF_LINES_IN_FILE_2; i++) {
//		printf("%d	*%29" PRIu64 "	*	%29" PRIu64 "	*\n", i, sorted_tables->table_2[i].key, sorted_tables->table_2[i].payload);
//	sleep(5);	
//	}
// Merging tables
	printf("*****	Merging tables		*****\n");
	merge (root, sorted_tables, official_tables);
// Deleting everything - Shutdown
	printf("*****	Shuting Down smj	*****\n");
	destroy_buffers (root);
	free(official_tables->table_1);
	free(official_tables->table_2);
	free(official_tables);
	free(sorted_tables->table_1);
	free(sorted_tables->table_2);
	free(sorted_tables);
	return 0;
}
