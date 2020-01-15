#ifndef _DATA_H_
#define _DATA_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "consts.h"

typedef struct bytes {
	unsigned char byte[8];
} bytes;

typedef struct row {
	uint64_t *value;
	uint64_t *need;
} row;

typedef struct table {
	uint64_t lines;
	uint64_t columns;
	row *rows;
	bytes *bin;	
} table;

typedef struct database {
	table *tables;
} database;

void free_database (database *database, int total_tables);

#endif
