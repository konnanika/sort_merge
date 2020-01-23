#include "read.h"

// Initialize the temp_table
void init_table (int table[MAX_NUM_OF_BOOLEAN]) {
	int j = 0;
	for (j=0; j<MAX_NUM_OF_BOOLEAN; j++) {
		table[j] = 0;
	}
}

void init_row (row *row) {
	row->I_small = 0;
	row->U_big = 0;
	row->F_count = 0;
	row->D_distinct = 0;
}

void read_binary_files (input *files, database *database) {
// Variables
	int i = 0;
	int s = 0;
	uint64_t n = 0;
	uint64_t m = 0;
	uint64_t j = 0;
	uint64_t count = 0;
	uint64_t temp_min = 1000999999999999999999999999;
	uint64_t temp_max = 0;
	int *temp_boolean;
	uint64_t sum_of_distinct = 0;
	uint64_t temp_distinct = 0;
	FILE *file;
// Reading the files
	for (i=0; i<files->total_tables; i++) {
		file = fopen(files->filenames[i], "rb");
		fread(&database->tables[i].lines, 8, 1, file);
		fread(&database->tables[i].columns, 8, 1, file);
		database->tables[i].rows = malloc(database->tables[i].columns * sizeof(struct row));
		for (n=0; n<database->tables[i].columns; n++) {
			database->tables[i].rows[n].value = malloc(database->tables[i].lines * sizeof(uint64_t));
			for (m=0; m<database->tables[i].lines; m++) {
				fread(&database->tables[i].rows[n].value[m], 8, 1, file);
				if (temp_min > database->tables[i].rows[n].value[m]){
					temp_min = database->tables[i].rows[n].value[m];
				}
				if (temp_max < database->tables[i].rows[n].value[m]){
					temp_max = database->tables[i].rows[n].value[m];
				}
				count ++;
			}
			// Find how many distinct values
			temp_boolean = malloc((MAX_NUM_OF_BOOLEAN-temp_min) * sizeof(int));
			for (s=0; s<(MAX_NUM_OF_BOOLEAN-temp_min); s++) {
				temp_boolean[s] = 0;
			}
			//init_table(&temp_boolean);
			init_row(&database->tables[i].rows[n]);
			for (m=0; m<database->tables[i].lines; m++) {
				temp_distinct = (database->tables[i].rows[n].value[m] %(MAX_NUM_OF_BOOLEAN-temp_min));
				temp_boolean[temp_distinct] = 1;
			}
			for (j=0; j<(MAX_NUM_OF_BOOLEAN-temp_min); j++) {
				sum_of_distinct = sum_of_distinct + temp_boolean[j];
			}
			database->tables[i].rows[n].I_small    = temp_min;
			database->tables[i].rows[n].U_big      = temp_max;
			database->tables[i].rows[n].F_count    = count;
			database->tables[i].rows[n].D_distinct = sum_of_distinct;
			printf("F = ");
			printf("%" PRIu64 "\n",database->tables[i].rows[n].F_count);
			printf("D = ");
			printf("%" PRIu64 "\n",database->tables[i].rows[n].D_distinct);
			printf("I = ");
			printf("%" PRIu64 "\n",database->tables[i].rows[n].I_small);
			printf("U = ");
			printf("%" PRIu64 "\n",database->tables[i].rows[n].U_big);
			free(temp_boolean);
			sum_of_distinct = 0;
			count = 0;
		}
		fclose(file);
	}
}
