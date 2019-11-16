#ifndef _UNSORTED_H_
#define _UNSORTED_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "consts.h"

typedef struct unsorted_record {
	int rowID;
	int key;
	unsigned char bin[8];
} unsorted_record;

typedef struct unsorted_tables {
	unsorted_record *table_1;
	unsorted_record *table_2;
} unsorted_tables;

#endif
