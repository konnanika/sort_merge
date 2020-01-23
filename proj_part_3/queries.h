#ifndef _QUERIES_H_
#define _QUERIES_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <math.h>

#include "consts.h"
#include "data.h"

typedef struct smj {
	int table_1;
	int key_1;
	uint64_t I_small_1;
	uint64_t U_big_1;
	uint64_t F_count_1;
	uint64_t D_distinct_1;
	int table_2;
	int key_2;
	uint64_t I_small_2;
	uint64_t U_big_2;
	uint64_t F_count_2;
	uint64_t D_distinct_2;
} smj;

typedef struct filter {
	int table;
	int key;
	char symbol;
	uint64_t number;
	uint64_t I_small;
	uint64_t U_big;
	uint64_t F_count;
	uint64_t D_distinct;
} filter;

typedef struct sum {
	int table;
	int key;
	uint64_t result;
} sum;

typedef struct query {
	int null;
	int *involved_tables;
	int num_of_tables;
	int num_of_smjs;
	int num_of_filters;
	int num_of_sums;
	smj *predicates_smj;
	filter *predicates_filter;
	sum *result_sum;
} query;

typedef struct unsorted_record {
	uint64_t row;
	uint64_t key;
	unsigned char bin[8];
	uint64_t rowID;
} unsorted_record;

typedef struct unsorted_table {
	unsorted_record *table;
	uint64_t num_of_records;
} unsorted_table;

typedef struct unsorted_tables {
	unsorted_table *tables;
} unsorted_tables;

typedef struct sorted_record {
	uint64_t key;
	int rowID;
} sorted_record;

typedef struct sorted_tables {
	sorted_record *table_1;
	sorted_record *table_2;
} sorted_tables;

typedef struct histogram {
	int value;
	unsorted_record *temp_table;
} histogram;

typedef struct merged {
	uint64_t *rowID_1; // may refer to merge
	uint64_t *rowID_2; // always to database
} merged;

void init_unsorted_tables (unsorted_tables *unsorted_tables, database *database, query *queries, int q);

void init_sorted_tables (sorted_tables *sorted_tables, uint64_t size_1, uint64_t size_2);

void fill_bin_tables (unsorted_tables *Unsorted_tables, int table_1, int table_2);

void sort (unsorted_record *unsorted_table, sorted_record *sorted_table, int position, int records, int byte);

void quicksort (unsorted_record *unsorted_table, int first, int last);

void init_query (query *query);

void init_histogram (histogram *hist);

void init_psum (int psum[256]);

void free_queries (query *queries);

void queries_execution (query *queries, database *database);

uint64_t merge_count (sorted_tables *sorted_tables, uint64_t records_1, uint64_t records_2);

void merge (sorted_tables *sorted_tables, merged *result, uint64_t records_1, uint64_t records_2);

void queries_statistics(database *database, query *queries);

#endif
