#ifndef _CONSTS_H_
#define _CONSTS_H_

#define INPUT_LINE_MAX_LENGTH       				256             // Maximum length for each line in input file
#define FILENAME_MAX_LENGTH							128				// Maximum length of the name of a file
#define NUM_OF_LINES_IN_FILE_1						100000000			// Number of lines in first file
#define NUM_OF_LINES_IN_FILE_2						100000000			// Number of lines in second file
#define NUM_OF_COLLUMNS_IN_FILE_1					2				// Number of collumns in first file
#define NUM_OF_COLLUMNS_IN_FILE_2					2				// Number of collumns in second file
#define MAX_NUM_OF_RECORDS_IN_TEMP_SORTED_TABLE		100000000			// Maximum size of temporary table
#define MAX_NUM_FOR_QUICKSORT						8192			// Number of records in a table to quicksort
#define SIZE_OF_THE_BUFFER							41666			// NUmber of records in a buffer of 1MB
#define MAX_NUM_OF_INPUT_FILES						100
#define MAX_RECORDS									100000000
#define MAX_NUM_OF_QUERIES							100
#define MAX_NUM_OF_FILTERS							100
#define MAX_NUM_OF_SMJS								100
#define MAX_NUM_OF_SUMS								100
#define STRING_LENGTH								100

#define tesrelA										3				// Number of lines in first unit test file
#define tesrelB										2				// Number of lines in second unit test file
#define tinrelA										1000			// Number of lines in first tiny file
#define tinrelB										2000			// Number of lines in second tiny file
#define smarelA										10000			// Number of lines in first small file
#define smarelB										30000			// Number of lines in second small file
#define medrelA										100000			// Number of lines in first medium file
#define medrelB										1000000			// Number of lines in second medium file

#define NUMOF_QUERY_THREADS 5
#define NUMOF_QUERIES 5
#define NUMOF_SORT_THREADS 5
#define NUMOF_MERGE_THREADS 5

#endif
