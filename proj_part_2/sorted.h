#ifndef _SORTED_H_
#define _SORTED_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "consts.h"
#include "unsorted.h"

typedef struct sorted_record {
	int rowID;
	int key;
} sorted_record;

typedef struct sorted_tables {
	sorted_record *table_1;
	sorted_record *table_2;
} sorted_tables;

#endif
