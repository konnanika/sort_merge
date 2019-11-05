#ifndef _PARCER_H_
#define _PARCER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "consts.h"
#include "structs.h"
#include "helpers.h"

/**
 * Parse an entire graph from the stream pointed to by file
 * @param The struct where the tables will be stored
 * @param The name of the first file
 * @param The name of the second file
 */
void parse_input_file(tables *official_tables, char input_file_name_1[FILENAME_MAX_LENGTH],	char input_file_name_2[FILENAME_MAX_LENGTH]);

#endif
