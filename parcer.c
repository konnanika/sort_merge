#include "parcer.h"
// Parse 2 files and fill 2 unsorted tables
void parse_input_file(unsorted_tables *unsorted_tables, char input_file_name_1[FILENAME_MAX_LENGTH],	char input_file_name_2[FILENAME_MAX_LENGTH]) {
// Variables
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	char *token;
	char comma[2] = ",";
	int record_counter = 0;
// Read from file 1
	file = fopen(input_file_name_1, "r");
	if (file == NULL) {
		printf("*****	Error in file 1		*****\n");
		exit(1);
	}
	while ((read = getline(&line, &len, file)) != -1) {
        line[strlen(line)-1] = '\0';
        token = strtok(line,comma);
        unsorted_tables->table_1[record_counter].key = atouint64_t(token);
        token = strtok(NULL, comma);
        unsorted_tables->table_1[record_counter].payload = atouint64_t(token);
        unsorted_tables->table_1[record_counter].rowID = record_counter;
        record_counter++;
    }
    fclose(file);
// Read from file 2
	record_counter = 0;
	file = fopen(input_file_name_2, "r");
	if (file == NULL) {
		printf("*****	Error in file 2		*****\n");
		exit(1);
	}
	while ((read = getline(&line, &len, file)) != -1) {
        line[strlen(line)-1] = '\0';
        token = strtok(line,comma);
        unsorted_tables->table_2[record_counter].key = atouint64_t(token);
        token = strtok(NULL, comma);
        unsorted_tables->table_2[record_counter].payload = atouint64_t(token);
        unsorted_tables->table_2[record_counter].rowID = record_counter;
        record_counter++;
    }
    fclose(file);
    if (line)
    	free(line);
}
