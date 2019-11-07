#ifndef _TEST_PARSER_H_
#define _TEST_PARSER_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <inttypes.h>

#include "../consts.h"
#include "../unsorted.h"
#include "../parser.h"
#include "../helpers.h"

void test_parse_input_file (unsorted_tables *Unsorted_tables, char test_input_file_name_1[FILENAME_MAX_LENGTH], char test_input_file_name_2[FILENAME_MAX_LENGTH]);

#endif
