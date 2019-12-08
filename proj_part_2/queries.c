#include "queries.h"

void init_query (query *query) {
	query->num_of_smjs = 0;
	query->num_of_filters = 0;
	query->num_of_sums = 0;
}

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
		for (i=0; i<queries[q].num_of_filters; i++) {
		
		}
		q++;
	}
}
