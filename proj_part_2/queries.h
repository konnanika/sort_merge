#ifndef _QUERIES_H_
#define _QUERIES_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "consts.h"
#include "data.h"

typedef struct smj {
	int table_1;
	int key_1;
	int table_2;
	int key_2;
} smj;

typedef struct filter {
	int table;
	int key;
	char symbol;
	uint64_t number;
} filter;

typedef struct sum {
	int table;
	int key;
	uint64_t result;
} sum;

typedef struct query {
	int null;
	table *result;
	int *involved_tables;
	int num_of_smjs;
	int num_of_filters;
	int num_of_sums;
	smj *predicates_smj;
	filter *predicates_filter;
	sum *result_sum;
} query;

void init_query (query *query);

void free_queries (query *queries);
//void queries_execution (query *queries, database *database);

#endif
