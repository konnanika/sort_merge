#ifndef _UNSORTED_H_
#define _UNSORTED_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "consts.h"

/*
 * Struct for the record of an unsorted table
 */
typedef struct unsorted_record {
	uint64_t key;
	uint64_t payload;
	unsigned char bin[8];
	int rowID;
} unsorted_record;
/*
 * Struct for the 2 unsorted tables from the 2 files
 */
typedef struct unsorted_tables {
	unsorted_record *table_1;
	unsorted_record *table_2;
} unsorted_tables;

/*
 * Initialize the 2 unsorted tables
 * @param Pointer to the struct of the 2 unsorted tables
 * RETURNS void
 */
void init_unsorted_tables (unsorted_tables *unsorted_tables);
/*
 * Fill, for each unsorted_record, a table (size of 8 bytes)
 * where each element has the unsigned value of each byte
 * @param Pointer to the struct of the 2 unsorted tables
 * RETURNS void
 */
void fill_bin_table (unsorted_tables *unsorted_tables);
/*
 * Print an unsorted table
 * @param Pointer to the unsorted table
 * @param Number of records in the table
 * RETURNS void
 */
void print_unsorted_table (unsorted_record *table_1, int records);

#endif
