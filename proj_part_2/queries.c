#include "queries.h"

void init_query (query *query) {
	query->num_of_smjs = 0;
	query->num_of_filters = 0;
	query->num_of_sums = 0;
	query->num_of_tables = 0;
}

void free_queries (query *queries) {
	int i = 0;
	int j = 0;
	for (i=0; i<MAX_NUM_OF_QUERIES; i++) {
		if (queries[i].num_of_smjs == -1)
			break;
		free(queries[i].predicates_smj);
		free(queries[i].predicates_filter);
		free(queries[i].result_sum);
		free(queries[i].involved_tables);
	}
	free(queries);
}

void queries_execution (query *queries, database *database) {
// Random Variables
	int i = 0;
	int f = 0;
	int has_filter = 0;
	uint64_t j = 0;
	uint64_t k = 0;
	uint64_t p = 0;
	uint64_t n = 0;
	uint64_t temp = 0;
	uint64_t compare = 255;
	int q = 0;
// Database Variables
	int total_tables = 0;
	struct database *temp_database;
	printf("starting queries");
// For each query
	while (queries[q].num_of_smjs != -1) {
		total_tables = sizeof(queries[q].involved_tables) / sizeof(int);
		temp_database = malloc(sizeof(struct database));
		temp_database->tables = malloc(total_tables * sizeof(struct table));
		for (j=0; j<total_tables; j++) {
			has_filter = 0;
			for (f=0; f<queries[q].num_of_filters; f++) {
				if (queries[q].involved_tables[j] == queries[q].predicates_filter[f].table)
					has_filter = 1;
					break;
			}
			if (has_filter == 0) {
				temp_database->tables[j].columns = database->tables[queries[q].involved_tables[j]].columns;
				temp_database->tables[j].lines = database->tables[queries[q].involved_tables[j]].lines;
				temp_database->tables[j].rows = malloc(temp_database->tables[j].columns * sizeof(struct row));
				for (i=0; i<database->tables[queries[q].involved_tables[j]].columns; i++) {
					temp_database->tables[j].rows[i].value = malloc(temp_database->tables[j].lines * sizeof(uint64_t));
					for (k=0; k<database->tables[queries[q].involved_tables[j]].lines; k++) {
						temp_database->tables[j].rows[i].value[k] = database->tables[queries[q].involved_tables[j]].rows[i].value[k];
					}
				}
			} else {
				n = 0;
				database->tables[j].rows[queries[q].predicates_filter[f].key].need = malloc(temp_database->tables[j].lines * sizeof(uint64_t));
				for (k=0; k<database->tables[queries[q].involved_tables[j]].lines; k++) {
					if (queries[q].predicates_filter[f].symbol == '=') {
						if (temp_database->tables[j].rows[queries[q].predicates_filter[f].key].value[k] == queries[q].predicates_filter[f].number) {
							database->tables[j].rows[queries[q].predicates_filter[f].key].need[k] = 1;
							n++;
						} else {
							database->tables[j].rows[queries[q].predicates_filter[f].key].need[k] = 0;
						}
					} else if (queries[q].predicates_filter[f].symbol == '>') {
						if (temp_database->tables[j].rows[queries[q].predicates_filter[f].key].value[k] > queries[q].predicates_filter[f].number) {
							database->tables[j].rows[queries[q].predicates_filter[f].key].need[k] = 1;
							n++;
						} else {
							database->tables[j].rows[queries[q].predicates_filter[f].key].need[k] = 0;
						}
					}else if (queries[q].predicates_filter[f].symbol == '<') {
						if (temp_database->tables[j].rows[queries[q].predicates_filter[f].key].value[k] < queries[q].predicates_filter[f].number) {
							database->tables[j].rows[queries[q].predicates_filter[f].key].need[k] = 1;
							n++;
						} else {
							database->tables[j].rows[queries[q].predicates_filter[f].key].need[k] = 0;
						}
					}
				}
				temp_database->tables[j].columns = database->tables[queries[q].involved_tables[j]].columns;
				temp_database->tables[j].lines = n;
				temp_database->tables[j].rows = malloc(temp_database->tables[j].columns * sizeof(struct row));
				for (i=0; i<database->tables[queries[q].involved_tables[j]].columns; i++) {
					temp_database->tables[j].rows[i].value = malloc(n * sizeof(uint64_t));
					p = 0;
					for (k=0; k<database->tables[queries[q].involved_tables[j]].lines; k++) {
						if (database->tables[j].rows[queries[q].predicates_filter[f].key].need[k] == 1)
							temp_database->tables[j].rows[i].value[p] = database->tables[queries[q].involved_tables[j]].rows[i].value[k];
							p++;
					}
				}
								
			}
			free(database->tables[j].rows[queries[q].predicates_filter[f].key].need);
		}
		for (i=0; i<database->tables[0].lines; i++)
			printf("	%29" PRIu64 "\n", database->tables[0].rows[0].value[i]);
	}
}












/*




void queries_execution (query *queries, database *database) {
// Random Variables
	int i = 0;
	uint64_t j = 0;
	uint64_t k = 0;
	uint64_t n = 0;
	int q = 0;
// Database Variables
	int total_tables = 0;
	struct database *temp_database;
// For each query
	while (queries[q].involved_tables != NULL) {
		total_tables = sizeof(queries[q].involved_tables) / sizeof(int);
		temp_database = malloc(sizeof(struct database));
		temp_database->tables = malloc(total_tables * sizeof(struct table));
	// Copying involved tables in a temporary database
		for (i=0; i<total_tables; i++) {
			temp_database->tables[i].columns = database->tables[queries[q].involved_tables[i]].columns;
			temp_database->tables[i].lines = database->tables[queries[q].involved_tables[i]].lines;
			for (j=0; j<database->tables[queries[q].involved_tables[i]].columns; j++) {
				for (k=0; k<database->tables[queries[q].involved_tables[i]].lines; k++) {
					temp_database->tables[i].rows[j].value[k] = database->tables[queries[q].involved_tables[i]].rows[j].value[k];
				}
			}
		}
	// Applying filters
		for (i=0; i<queries[q].num_of_filters; i++) {
			for (k=0; k<temp_database->tables[queries[q].predicates_filter[i].table].lines; k++) {
				n = 0;
				if (queries[q].predicates_filter[i].symbol == '=') {
					if (temp_database->tables[queries[q].predicates_filter[i].table].rows[queries[q].predicates_filter[i].key].value[k] == queries[q].predicates_filter[i].number) {
						for (j=0; j<temp_database->tables[queries[q].predicates_filter[i].table].columns; j++) {
							temp_database->tables[queries[q].predicates_filter[i].table].rows[j].value[n] = temp_database->tables[queries[q].predicates_filter[i].table].rows[j].value[k];
							n++;
						}
					}
				} else if (queries[q].predicates_filter[i].symbol == '>') {
					if (temp_database->tables[queries[q].predicates_filter[i].table].rows[queries[q].predicates_filter[i].key].value[k] > queries[q].predicates_filter[i].number) {
						for (j=0; j<temp_database->tables[queries[q].predicates_filter[i].table].columns; j++) {
							temp_database->tables[queries[q].predicates_filter[i].table].rows[j].value[n] = temp_database->tables[queries[q].predicates_filter[i].table].rows[j].value[k];
							n++;
						}
					}
				} else if (queries[q].predicates_filter[i].symbol == '<') {
					if (temp_database->tables[queries[q].predicates_filter[i].table].rows[queries[q].predicates_filter[i].key].value[k] < queries[q].predicates_filter[i].number) {
						for (j=0; j<temp_database->tables[queries[q].predicates_filter[i].table].columns; j++) {
							temp_database->tables[queries[q].predicates_filter[i].table].rows[j].value[n] = temp_database->tables[queries[q].predicates_filter[i].table].rows[j].value[k];
							n++;
						}
					}
				}
			}
			temp_database->tables[queries[q].predicates_filter[i].table].lines = n;
		}
	// Running smjs
		for (i=0; i<queries[q].num_of_smjs; i++) {
			fill_bin_tables (temp_database, temp_database->tables[queries[q].predicates_smjs[i].table_1], queries[q].predicates_smjs[i].key_1, temp_database->tables[queries[q].predicates_smjs[i].table_2], queries[q].predicates_smjs[i].key_2);
		}
		q++;
	}
}*/
