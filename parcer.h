#ifndef _PARCER_H_
#define _PARCER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "consts.h"
#include "unsorted.h"
#include "helpers.h"

/*
 * Parse 2 files and fill 2 unsorted tables
 * @param Pointer to the struct of the 2 unsorted tables
 * @param The name of the first file
 * @param The name of the second file
 */
void parse_input_file(unsorted_tables *unsorted_tables, char input_file_name_1[FILENAME_MAX_LENGTH], char input_file_name_2[FILENAME_MAX_LENGTH]);

#endif
