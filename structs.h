#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "consts.h"

typedef struct record {
	uint64_t key;
	uint64_t payload;
	unsigned char bin[8];
	int rowID;
} record;

typedef struct tables {
	record *table_1;
	record *table_2;
} tables;

typedef struct merged_record {
    uint64_t key;
    uint64_t payload_A;
    uint64_t payload_B;
} merged_record;

typedef struct buffer {
    struct buffer* next;
    merged_record table[41666];
} buffer;

typedef struct histogram {
	int value;
	record *temp_table;
} histogram;

void init_tables (tables *tables);

void init_buffer (buffer *buffer);

buffer *new_buffer (buffer *old);

void destroy_buffers (buffer *buffer);

void fill_bin_table (tables *tables);

void sort (record *unsorted_table, record *sorted_table, int position, int records, int byte);

void quicksort (record *unsorted_table, int first, int last);

void merge (buffer *buffer, tables *sorted_tables, tables *unsorted_tables);

#endif
