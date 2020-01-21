#include "data.h"

void free_database (database *database, int total_tables) {
	int i = 0;
	uint64_t j = 0;
	for (i=0; i<total_tables; i++) {
		for (j=0; j<database->tables[i].columns; j++)
			free(database->tables[i].rows[j].value);
		free(database->tables[i].rows);
	}
	free(database->tables);
	free(database);
}
