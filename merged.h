#ifndef _MERGED_H_
#define _MERGED_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "consts.h"
#include "unsorted.h"
#include "sorted.h"

/*
 * Struct for the record of merged table
 */
typedef struct merged_record {
    uint64_t key;
    uint64_t payload_A;
    uint64_t payload_B;
} merged_record;
/*
 * Struct for the buffer of merged table
 */
typedef struct buffer {
    struct buffer* next;
    merged_record table[SIZE_OF_THE_BUFFER];
} buffer;
/*
 * Initialize the buffer
 * @param Pointer to the buffer
 * RETURNS void
 */
void init_buffer (buffer *buffer);
/*
 * Create a new buffer and add it to the list
 * @param Pointer to the previous buffer
 * RETURNS pointer to the new buffer
 */
buffer *new_buffer (buffer *old);
/*
 * Destroy all the buffers
 * @param Pointer to the first buffer of the list
 * RETURNS void
 */
void destroy_buffers (buffer *buffer);
/*
 * Merge 2 sorted tables and save the records to the buffer list
 * @param Pointer to the root of the buffer list
 * @param Pointer to the struct of the sorted tables
 * @param Pointer to the struct of the unsorted tables
 * RETURNS void
 */
void merge (buffer *buffer, sorted_tables *sorted_tables, unsorted_tables *unsorted_tables);
/*
 * Print a merged table
 * @param Pointer to the root of the buffer list
 * RETURNS void
 */
void print_merged_table (buffer *buffer);

#endif
