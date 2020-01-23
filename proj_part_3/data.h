#ifndef _DATA_H_
#define _DATA_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>
#include <limits.h>

#include "consts.h"

typedef struct row {
	uint64_t *value;
	uint64_t I_small;
	uint64_t U_big;
	uint64_t F_count;
	uint64_t D_distinct;
} row;

typedef struct table {
	uint64_t lines;
	uint64_t columns;
	row *rows;
} table;

typedef struct database {
	table *tables;
} database;

void free_database (database *database, int total_tables);

#endif
