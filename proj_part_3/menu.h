#ifndef _MENU_H_
#define _MENU_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "consts.h"
#include "queries.h"

typedef struct input {
	int total_tables;
	char filenames[MAX_NUM_OF_INPUT_FILES][FILENAME_MAX_LENGTH];
} input;

void input_menu (input *files);

void queries_menu (query *queries);

#endif
