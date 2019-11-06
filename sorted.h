#ifndef _SORTED_H_
#define _SORTED_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "consts.h"
#include "unsorted.h"

/*
 * Struct for the record of an sorted table
 */
typedef struct sorted_record {
	uint64_t key;
	int rowID;
} sorted_record;
/*
 * Struct for the 2 sorted tables from the 2 unsorted tables
 */
typedef struct sorted_tables {
	sorted_record *table_1;
	sorted_record *table_2;
} sorted_tables;
/*
 * Struct for histogram used to sort one unsorted table
 */
typedef struct histogram {
	int value;
	unsorted_record *temp_table;
} histogram;
/*
 * Initialize the 2 sorted tables
 * @param Pointer to the struct of the 2 sorted tables
 * RETURNS void
 */
void init_sorted_tables (sorted_tables *sorted_tables);
/*
 * Initialize the histogram
 * @param Pointer to the stuct of the histogram
 * RETURNS void
 */
void init_histogram (histogram *hist);
/*
 * Initialize the psum
 * @param The psum table
 * RETURNS void
 */
void init_psum (int psum[256]);
/*
 * Read an unsorted table and fill a sorted table recursively
 * @param Pointer to an unsorted table
 * @param Pointer to a sorted table
 * @param Position of the sorted table the next record will be written to
 * @param Number of records in the unsorted table
 * @param Which byte of the numbers we are sorting with
 * RETURNS void
 */
void sort (unsorted_record *unsorted_table, sorted_record *sorted_table, int position, int records, int byte);
/*
 * Read an unsorted table and sort them in the same table recursively
 * @param Pointer to an unsorted table
 * @param The position of the first record we want to sort
 * @param The position of the last record we want to sort
 * RETURNS void
 */
void quicksort (unsorted_record *unsorted_table, int first, int last);
/*
 * Print a sorted table
 * @param Pointer to the sorted table
 * @param Number of records in the table
 * RETURNS void
 */
void print_sorted_table (sorted_record *table, int records);

#endif
