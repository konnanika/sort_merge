#include "queries.h"

void init_query (query *query) {
	query->num_of_smjs = 0;
	query->num_of_filters = 0;
	query->num_of_sums = 0;
	query->num_of_tables = 0;
}

void free_queries (query *queries) {
	int i = 0;
	int j = 0;
	for (i=0; i<MAX_NUM_OF_QUERIES; i++) {
		if (queries[i].num_of_smjs == -1)
			break;
		free(queries[i].predicates_smj);
		free(queries[i].predicates_filter);
		free(queries[i].result_sum);
		free(queries[i].involved_tables);
	}
	free(queries);
}

void init_unsorted_tables (unsorted_tables *unsorted_tables, database *database, query *queries, int q) {
	int i = 0;
	unsorted_tables->tables = malloc(queries[q].num_of_tables * sizeof(unsorted_record) * MAX_RECORDS);
	for (i=0; i<queries[q].num_of_tables; i++)
		unsorted_tables->tables[i].table = malloc(sizeof(unsorted_record) * MAX_RECORDS);
}

void init_sorted_tables (sorted_tables *sorted_tables, uint64_t size_1, uint64_t size_2) {
	sorted_tables->table_1 = (sorted_record*)malloc(sizeof(sorted_record) * size_1);
	sorted_tables->table_2 = (sorted_record*)malloc(sizeof(sorted_record) * size_2);
}
// Initialize the histogram
void init_histogram (histogram *hist) {
	int j = 0;
	for (j=0; j<256; j++) {
		hist[j].value = 0;
		hist[j].temp_table = (unsorted_record*)malloc(sizeof(unsorted_record) * MAX_RECORDS);
	}
}
// Initialize the psum
void init_psum (int psum[256]) {
	int j = 0;
	for (j=0; j<256; j++) {
		psum[j] = 0;
	}
}
// Fill, for each unsorted_record, a table (size of 8 bytes)
// where each element has the unsigned value of each byte
void fill_bin_tables (unsorted_tables *Unsorted_tables, int table_1, int table_2) {
// Variables
	int i = 0;
	int j = 0;
	uint64_t temp = 0;
	uint64_t compare = 255;
// Fill bin tables in records from file 1
	for (i=0; i<Unsorted_tables->tables[table_1].num_of_records; i++) {
		temp = Unsorted_tables->tables[table_1].table[i].key;
		Unsorted_tables->tables[table_1].table[i].bin[0] = temp & compare;
		for (j=1; j<8; j++) {
			temp = temp>>8;
			Unsorted_tables->tables[table_1].table[i].bin[j] = temp & compare;
		}
	}
// Fill bin tables in records from file 2
	for (i=0; i<Unsorted_tables->tables[table_2].num_of_records; i++) {
		temp = Unsorted_tables->tables[table_2].table[i].key;
		Unsorted_tables->tables[table_2].table[i].bin[0] = temp & compare;
		for (j=1; j<8; j++) {
			temp = temp>>8;
			Unsorted_tables->tables[table_2].table[i].bin[j] = temp & compare;
		}
	}
}
// Read an unsorted table and sort them in the same table recursively
void sort (unsorted_record *unsorted_table, sorted_record *sorted_table, int position, int records, int byte) {
// Variables
	int i = 0;
	int j = 0;
	int x = 0;
	int z = 0;
	int current_position = 0;
// Temporary Database Variables
	histogram *hist = malloc(sizeof(histogram)*256);;
	init_histogram (hist);
	int psum[256];
	init_psum (psum);
// Read the unsorted table and fill the histogram
	for (j=0; j<256; j++) {
		for (i=0; i<records; i++) {
			if (unsorted_table[i].bin[byte] - j == 0) {
				hist[j].temp_table[hist[j].value] = unsorted_table[i];
				hist[j].value++;
			}
		}
	}
// Fill the psum
	i = 0;
	for (j=0; j<256; j++) {
		psum[j] = i;
		i = i + hist[j].value;
	}
// Read the unsorted table in 1 position of the histogram
	for (j=0; j<256; j++) {
	// Insert the records to the sorted table if checking the last byte
		if (hist[j].value != 0 && byte == 0) {
			z = 0;
			current_position = psum[j]+position + hist[j].value;
			for (x=psum[j]+position; x<current_position; x++) {
				sorted_table[x].key = hist[j].temp_table[z].key;
				sorted_table[x].rowID = hist[j].temp_table[z].rowID;
				z++;
			}
	// Run quicksort it is possible and insert the records to the sorted table
		} else if (hist[j].value <= MAX_NUM_FOR_QUICKSORT && hist[j].value != 0) {
			quicksort(hist[j].temp_table, 0, hist[j].value - 1);
			z = 0;
			current_position = psum[j]+position + hist[j].value;
			for (x=psum[j]+position; x<current_position; x++) {
				sorted_table[x].key = hist[j].temp_table[z].key;
				sorted_table[x].rowID = hist[j].temp_table[z].rowID;
				z++;
			}
	// Run sort recursively if quicksort is not possible
		} else if (hist[j].value > MAX_NUM_FOR_QUICKSORT) {
			sort(hist[j].temp_table, sorted_table, psum[j]+position, hist[j].value, byte-1);
		}
	}
	sleep(1);
// Destroy the histogram
	for (j=0; j<256; j++) {
		free(hist[j].temp_table);
	}
	free(hist);
}
// Read an unsorted table and sort them in the same table recursively
void quicksort (unsorted_record *unsorted_table, int first, int last) {
// Variables
	int i = 0;
	int j = 0;
	int pivot = 0;
	unsorted_record temp;
// Quicksort with pivot the first record
	if (first<last) {
    	pivot = first;
    	i = first;
    	j = last;
    // Read the table from first and from last as long as its not the same record
		while (i<j) {
		// Read first to last and stop if you find a record with higher key than the pivot
			while (unsorted_table[i].key<=unsorted_table[pivot].key && i<last)
				i++;
		// Read last to first and stop if you find a record with lower or equal key than the pivot
			while (unsorted_table[j].key>unsorted_table[pivot].key)
				j--;
		// If the records i and j are not in the right place
			if (i<j) {
			// Swap them
				temp = unsorted_table[i];
				unsorted_table[i] = unsorted_table[j];
				unsorted_table[j] = temp;
			}
		}
	// Swap j with pivot
		temp = unsorted_table[pivot];
		unsorted_table[pivot] = unsorted_table[j];
		unsorted_table[j] = temp;
	// Run quicksort recursively 1 time for each subtable
		quicksort(unsorted_table,first,j-1);
		quicksort(unsorted_table,j+1,last);
	}
}

void queries_execution (query *queries, database *database) {
// Random Variables
	int i = 0;
	int f = 0;
	int has_filter = 0;
	uint64_t j = 0;
	uint64_t total = 0;
	uint64_t sum = 0;
	uint64_t k = 0;
	uint64_t n = 0;
	int q = 0;
// Database Variables
	merged *result;
// For each query
	while (queries[q].num_of_smjs != -1) {
		result = malloc(queries[q].num_of_smjs * sizeof(merged));
		unsorted_tables *Unsorted_tables = malloc(sizeof(unsorted_tables));
		init_unsorted_tables (Unsorted_tables, database, queries, q);
	// Applying Filters
		for (j=0; j<queries[q].num_of_tables; j++) {
			has_filter = 0;
			for (f=0; f<queries[q].num_of_filters; f++) {
				if (queries[q].involved_tables[j] == queries[q].predicates_filter[f].table)
					has_filter = 1;
					break;
			}
			if (has_filter == 0) {
				for (i=0; i<database->tables[queries[q].involved_tables[j]].lines; i++) {
					Unsorted_tables->tables[j].table[i].rowID = i;
				}
				Unsorted_tables->tables[j].num_of_records = i;
			} else {
				n = 0;
				for (i=0; i<database->tables[queries[q].involved_tables[j]].lines; i++) {
					if (queries[q].predicates_filter[f].symbol == '=') {
						if (database->tables[j].rows[queries[q].predicates_filter[f].key].value[i] == queries[q].predicates_filter[f].number) {
							Unsorted_tables->tables[j].table[n].rowID = i;
							n++;
						}
					} else if (queries[q].predicates_filter[f].symbol == '>') {
						if (database->tables[j].rows[queries[q].predicates_filter[f].key].value[i] > queries[q].predicates_filter[f].number) {
							Unsorted_tables->tables[j].table[n].rowID = i;
							n++;
						}
					}else if (queries[q].predicates_filter[f].symbol == '<') {
						if (database->tables[j].rows[queries[q].predicates_filter[f].key].value[i] < queries[q].predicates_filter[f].number) {
							Unsorted_tables->tables[j].table[n].rowID = i;
							n++;
						}
					}
				}
			}
		}
	// For each SMJ
		for (f=0; f<queries[q].num_of_smjs; f++) {
			sorted_tables *Sorted_tables = malloc(sizeof(sorted_tables));
			init_sorted_tables (Sorted_tables, Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].num_of_records, Unsorted_tables->tables[queries[q].predicates_smj[f].table_2].num_of_records);
			k = 0;
			for (i=0; i<Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].num_of_records; i++) {
				Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].table[i].row = queries[q].predicates_smj[f].key_1;
				Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].table[i].key = database->tables[queries[q].involved_tables[queries[q].predicates_smj[f].table_1]].rows[Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].table[i].row].value[Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].table[i].rowID];
			}
			for (i=0; i<Unsorted_tables->tables[queries[q].predicates_smj[f].table_2].num_of_records; i++) {
				Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].table[i].row = queries[q].predicates_smj[f].key_2;
				Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].table[i].key = database->tables[queries[q].involved_tables[queries[q].predicates_smj[f].table_2]].rows[Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].table[i].row].value[Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].table[i].rowID];
			}
			fill_bin_tables (Unsorted_tables, queries[q].predicates_smj[f].table_1, queries[q].predicates_smj[f].table_2);
			sort (Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].table, Sorted_tables->table_1, 0, Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].num_of_records, 7);
			sort (Unsorted_tables->tables[queries[q].predicates_smj[f].table_2].table, Sorted_tables->table_2, 0, Unsorted_tables->tables[queries[q].predicates_smj[f].table_2].num_of_records, 7);
			total = merge_count (Sorted_tables, Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].num_of_records, Unsorted_tables->tables[queries[q].predicates_smj[f].table_2].num_of_records);
			result[f].rowID_1 = malloc(total * sizeof(uint64_t));
			result[f].rowID_2 = malloc(total * sizeof(uint64_t));
			merge (Sorted_tables, result, Unsorted_tables->tables[queries[q].predicates_smj[f].table_1].num_of_records, Unsorted_tables->tables[queries[q].predicates_smj[f].table_2].num_of_records);
			unsorted_tables *temp = malloc(sizeof(unsorted_tables));
			temp->tables = malloc((queries[q].num_of_tables-1) * sizeof(unsorted_record));
			for (i=0; i<(queries[q].num_of_tables-1); i++)
				temp->tables[i].table = malloc(sizeof(unsorted_record) * MAX_RECORDS);
			for (i=0; i<total; i++) {
				temp->tables[0].table[i].rowID = result[f].rowID_1[i];
				temp->tables[1].table[i].rowID = result[f].rowID_2[i];
			}
			for (j=2; j<queries[q].num_of_tables; j++) {
				for (i=0; i<total; i++) {
					temp->tables[j].table[i].rowID = Unsorted_tables->tables[j].table[i].rowID;
				}			
			}
			Unsorted_tables = temp;
			for (i=0; i<(queries[q].num_of_tables-1); i++)
				free(temp->tables[i].table);
			free(temp->tables);
			free(temp);
			free(Sorted_tables->table_1);
			free(Sorted_tables->table_2);
			free(Sorted_tables);
		}
	// For Each Sum
		for (f=0; f<queries[q].num_of_sums; f++) {
			for (j=0; j<total; j++) {
				if (queries[q].result_sum[f].table == queries[q].num_of_tables)
					sum = sum + (database->tables[queries[q].involved_tables[queries[q].result_sum[f].table]].rows[queries[q].result_sum[f].key].value[Unsorted_tables->tables[result[f].rowID_2[j]].table[result[f].rowID_2[j]].rowID]);
				else
					sum = sum + (database->tables[queries[q].involved_tables[queries[q].result_sum[f].table]].rows[queries[q].result_sum[f].key].value[Unsorted_tables->tables[result[f].rowID_1[j]].table[result[f].rowID_1[j]].rowID]);
			}
			printf("%" PRIu64 " ", sum);
		}
		printf("\n");
	// Free Everything
		for (i=0; i<2; i++)
			free(Unsorted_tables->tables[i].table);
		free(Unsorted_tables->tables);
		free(Unsorted_tables);
		for (i=0; i<queries[q].num_of_smjs; i++) {
			free(result[f].rowID_1);
			free(result[f].rowID_2);
		}
		free(result);
	}
}
// Count the merged result of 1 smj
uint64_t merge_count (sorted_tables *sorted_tables, uint64_t records_1, uint64_t records_2) {
// Variables
	int position_1 = 0;
	int position_2 = 0;
	int position_2_first = 0;
	int position_2_last = 0;
	int i = 0;
	uint64_t prev = -1;
	uint64_t total = 0;
// Read 1 record from the sorted table 1 from start to finish
	for (position_1=0; position_1<records_1; position_1++) {
	// Read 1 record from the sorted table 2 from first to last
		for (position_2=position_2_first; position_2<=position_2_last; position_2++) {
		// If the record from table 1 is higher from the record from table 2
			if (sorted_tables->table_1[position_1].key > sorted_tables->table_2[position_2].key) {
			// Read the next of last in table 2
				if (position_2_last < records_2 - 1) {
					position_2 = position_2_last;
					position_2_last++;
					position_2_first = position_2_last;
				}
		// If the record from table 1 is lower from the record from table 2
			} else if (sorted_tables->table_1[position_1].key < sorted_tables->table_2[position_2].key) {
			// Read the next in table 1
				break;
		// If the record from table 1 is equal to the record from table 2
			} else if (sorted_tables->table_1[position_1].key == sorted_tables->table_2[position_2].key) {
			// Count the record
				printf("New Merged Result\n");
				total++;
			// If there is a previous record in table 1
				if (sorted_tables->table_1[position_1].key != prev) {
				// If the table 2 is not finished
					if (position_2_last < records_2 - 1) {
					// If the next in table 2 is equal to the one we compare at the moment
						if (sorted_tables->table_2[position_2].key == sorted_tables->table_2[position_2 + 1].key) {
						// Move the last to the next record
							position_2_last++;
						}
					}
				}
			}
		}
	// Keep the key of the record from table 1 so it can be used during the next read
		prev = sorted_tables->table_1[position_1].key;
	}
// When its all done return total records
	return total;
}
// Merge 2 sorted tables and save the records to the buffer list
void merge (sorted_tables *sorted_tables, merged *result, uint64_t records_1, uint64_t records_2) {
// Variables
	int position_1 = 0;
	int position_2 = 0;
	int position_2_first = 0;
	int position_2_last = 0;
	int i = 0;
	uint64_t prev = -1;
// Read 1 record from the sorted table 1 from start to finish
	for (position_1=0; position_1<records_1; position_1++) {
	// Read 1 record from the sorted table 2 from first to last
		for (position_2=position_2_first; position_2<=position_2_last; position_2++) {
		// If the record from table 1 is higher from the record from table 2
			if (sorted_tables->table_1[position_1].key > sorted_tables->table_2[position_2].key) {
			// Read the next of last in table 2
				if (position_2_last < records_2 - 1) {
					position_2 = position_2_last;
					position_2_last++;
					position_2_first = position_2_last;
				}
		// If the record from table 1 is lower from the record from table 2
			} else if (sorted_tables->table_1[position_1].key < sorted_tables->table_2[position_2].key) {
			// Read the next in table 1
				break;
		// If the record from table 1 is equal to the record from table 2
			} else if (sorted_tables->table_1[position_1].key == sorted_tables->table_2[position_2].key) {
			// Insert the record to the buffer
				result->rowID_1[i] = sorted_tables->table_1[position_1].rowID;
				result->rowID_2[i] = sorted_tables->table_1[position_2].rowID;
				i++;
			// If there is a previous record in table 1
				if (sorted_tables->table_1[position_1].key != prev) {
				// If the table 2 is not finished
					if (position_2_last < records_2 - 1) {
					// If the next in table 2 is equal to the one we compare at the moment
						if (sorted_tables->table_2[position_2].key == sorted_tables->table_2[position_2 + 1].key) {
						// Move the last to the next record
							position_2_last++;
						}
					}
				}
			}
		}
	// Keep the key of the record from table 1 so it can be used during the next read
		prev = sorted_tables->table_1[position_1].key;
	}
}
