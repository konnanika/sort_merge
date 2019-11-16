#include "read.h"

void read_binary_files (input *files, database *database) {
// Variables
	int i = 0;
	int n = 0;
	int m = 0;
	FILE *file;
// Reading the files
	for (i=0; i<files->total_tables; i++) {
		table *table = malloc(sizeof(struct table));
		fopen(files->filenames[i], "rb");
		fread(&table->lines, 8, 1, file);
		fread(&table->columns, 8, 1, file);
		table->rows = malloc(table->lines * sizeof(row*));
		for (n=0; n<table->columns; n++) {
			for (m=0; m<table->lines; m++) {
				fread(&table->rows[n]->value[n], 8, 1, file);
			}
		}
		fclose(file);
	}
	free(file);
}
