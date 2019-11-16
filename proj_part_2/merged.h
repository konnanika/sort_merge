#ifndef _MERGED_H_
#define _MERGED_H_

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <inttypes.h>

#include "consts.h"
#include "unsorted.h"
#include "sorted.h"

typedef struct merged_record {
	int rowID_1;
	int key_1;
	int rowID_2;
	int key_2;
} merged_record;

#endif
