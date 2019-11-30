#include "read.h"

void read_binary_files (input *files, database *database) {
// Variables
	int i = 0;
	uint64_t n = 0;
	uint64_t m = 0;
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
			}
		}
		fclose(file);
		printf("\nskata\n");
	}
}
