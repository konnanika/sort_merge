#include "sql.h"

int main(int argc, char **argv) {
// Random Variables
	int i = 0;
// Database Variables
	input *files = malloc(sizeof(input));
	database *database = malloc(sizeof(struct database));
	query queries[MAX_NUM_OF_QUERIES];
// Reading the input filenames
	input_menu(files);
	database->tables = malloc(files->total_tables * sizeof(struct table));
// Reading the binary files
	read_binary_files (files, database);
// Reading the queries
	queries_menu(queries);
// Executing the queries
	queries_execution(queries, database);
// Shuting down
	free(files);
	free(database);
	return 0;
}
