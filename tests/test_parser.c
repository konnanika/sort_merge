#include "test_parser.h"
void test_parse_input_file (unsorted_tables *Unsorted_tables, char test_input_file_name_1[FILENAME_MAX_LENGTH],	char test_input_file_name_2[FILENAME_MAX_LENGTH]) {
	int result = 0;
	int i = 0;
	unsorted_tables *filled_Unsorted_tables = malloc(sizeof(unsorted_tables));
	init_unsorted_tables (filled_Unsorted_tables);
	filled_Unsorted_tables->table_1[0].key = 29742;
	filled_Unsorted_tables->table_1[0].payload = 321654987;
	filled_Unsorted_tables->table_1[1].key = 9874275;
	filled_Unsorted_tables->table_1[1].payload = 54897;
	filled_Unsorted_tables->table_1[2].key = 2315454315;
	filled_Unsorted_tables->table_1[3].payload = 0;
	filled_Unsorted_tables->table_2[0].key = 123456;
	filled_Unsorted_tables->table_2[0].payload = 987654;
	filled_Unsorted_tables->table_2[1].key = 987123456789;
	filled_Unsorted_tables->table_2[1].payload = 54854;
	Unsorted_tables = malloc(sizeof(unsorted_tables));
	init_unsorted_tables (Unsorted_tables);
	parse_input_file(Unsorted_tables, test_input_file_name_1, test_input_file_name_2);
	
	for (i=0; i<NUM_OF_LINES_IN_FILE_1; i++)
		if (filled_Unsorted_tables->table_1[i].key == Unsorted_tables->table_1[i].key && filled_Unsorted_tables->table_1[i].payload == Unsorted_tables->table_1[i].payload)
			result++;
	for (i=0; i<NUM_OF_LINES_IN_FILE_2; i++)
		if (filled_Unsorted_tables->table_2[i].key == Unsorted_tables->table_2[i].key && filled_Unsorted_tables->table_2[i].payload == Unsorted_tables->table_2[i].payload)
			result++;

	printf("\n$$ File <<parser.c>> Function <<parse_input_file>> test completed\n");
	if (result == 5)
		printf("$$	-->	Test passed	// Both valid and invalid input are treated accordingly\n");
	else if (result > 5)
		printf("$$	-->	Test failed	// Invalid input is considered valid\n");
	else if (result < 5)
		printf("$$	-->	Test failed	// Valid input is considered invalid\n");
}
