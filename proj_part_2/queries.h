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
	smj predicates_smj[MAX_NUM_OF_SMJS];
	filter predicates_filter[MAX_NUM_OF_FILTERS];
	sum result_sum[MAX_NUM_OF_SUMS];
} query;

void init_query (query query);

void queries_execution (query queries[MAX_NUM_OF_QUERIES], database *database);

#endif
