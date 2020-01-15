#include "sql.h"

int main(int argc, char **argv) {
// Random Variables
	int i = 0;
	int q = 0;
// Database Variables
	input *files = malloc(sizeof(input));
	database *database = malloc(sizeof(struct database));
	query *queries = malloc(MAX_NUM_OF_QUERIES * sizeof(struct query));
// Reading the input filenames
	input_menu(files);
	database->tables = malloc(files->total_tables * sizeof(struct table));
// Reading the binary files
	read_binary_files (files, database);
// Reading the queries
	queries_menu(queries);
	for(q=0; q<5; q++) {
		if (queries[q].num_of_smjs == -1)
			return 0;
		printf("The involved tables are: \n");
		for (i=0; i<queries[q].num_of_tables; i++){
			printf("%d ", queries[q].involved_tables[i]);
		}
		printf("\nThe joins that we need to do are: \n");
		for (i=0; i<queries[q].num_of_smjs; i++){
			printf("%d", queries[q].predicates_smj[i].table_1);
			printf(".%d=", queries[q].predicates_smj[i].key_1);
			printf("%d", queries[q].predicates_smj[i].table_2);	
			printf(".%d\n", queries[q].predicates_smj[i].key_2);
		}
		printf("\nThe filters that we need to do are: \n");
		for (i=0; i<queries[q].num_of_filters; i++){
			printf("%d", queries[q].predicates_filter[i].table);
			printf(".%d", queries[q].predicates_filter[i].key);
			printf("%c", queries[q].predicates_filter[i].symbol);	
			printf("%d\n", queries[q].predicates_filter[i].number);
		}
		printf("\nThe sums that we need to do are: \n");
		for (i=0; i<queries[q].num_of_sums; i++){
			printf("%d", queries[q].result_sum[i].table);
			printf(".%d\n", queries[q].result_sum[i].key);
		}
	}
// Executing the queries
	printf("\nExecuting the queries\n");
	queries_execution(queries, database);
// Shuting down
	free_database(database, files->total_tables);
	free_queries(queries);
	free(files);
	return 0;
}


//		0 1|0.1=1.1|0.1		0 1 2|0.1=1.1&1.0=2.0&0.1>4&1.1>10|0.0
//		0 1 2 3 4|3.1>101010&1.1=3.5&0.1>10&1.1>5&2.0>0&3.3>5&0.1=2.3&3.3>50574&3.1<5457|1.1 3.1
//		/home/user/Desktop/qwerasdf/r0

//		0 1 2 3 4 5|0.0=1.1&0.0=2.2&0.0=3.3&1.1=4.4&4.0=5.0&1.1>10|0.0

