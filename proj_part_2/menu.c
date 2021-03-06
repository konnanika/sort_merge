#include "menu.h"

void input_menu (input *files) {
// Variables
	int counter = 0;
	char *string;
	size_t stringsize = 32;
	size_t characters;
	char *filename;
	char enter[] = "\n";
// Menu Interface
	printf("Please type the names (or paths) of the binary table files :\n");
	while(1) {
		string = (char *)malloc(stringsize * sizeof(char));
		printf("	-->	");
		characters = getline(&string, &stringsize, stdin);
		if (strcmp(string, "Done\n") == 0) {
			free(string);
			break;
		}
		filename = strtok(string, enter);
		strcpy(files->filenames[counter], filename);
		counter++;
		files->total_tables = counter;
		free(string);
	}
}

void queries_menu (query *queries) {
// Variables
	int i = 0;
	int j = 0;
	int q = 0;
	int a = 0;
	int stop = 0;
	int chars = 0;
	char *string;
	char *token;
	char *token1;
	char temp[STRING_LENGTH];
	char tables[STRING_LENGTH];
	char predicates[STRING_LENGTH];
	char official_predicates[STRING_LENGTH];
	char sums[STRING_LENGTH];
	size_t stringsize = 32;
	size_t characters;
	char space[] = " ";
	int spaces = 0;
	char dot[] = ".";
	int dots = 0;
	char pipe[] = "|";
	int pipes = 0;
	char equal[] = "=";
	char greater[] = ">";
	char lower[] = "<";
	char ampersand[] = "&";
	int ampersands = 0;
	char enter[] = "\n";
// Menu Interface
	printf("Please type your queries :\n");
	while(1) {
		string = (char *)malloc(stringsize * sizeof(char));
		printf("	-->	");
	// Reading the query
		characters = getline(&string, &stringsize, stdin);
		if (string[0] == 'F') {
			queries[q].num_of_smjs = -1;
			free(string);
			break;
		}
		queries[q].predicates_filter = malloc(MAX_NUM_OF_FILTERS * (sizeof(struct filter)));
		queries[q].predicates_smj = malloc(MAX_NUM_OF_SMJS * sizeof(struct smj));
		queries[q].result_sum = malloc(MAX_NUM_OF_SUMS * sizeof(struct sum));
		init_query(&queries[q]);
	// Cutting the string of the query in 3 substrings
		token = strtok(string, pipe);
		strcpy(tables, token);
		token = strtok(NULL, pipe);
		strcpy(predicates, token);
		token = strtok(NULL, enter);
		strcpy(sums, token);
	// Reading which tables are required for this query
		for (i=0; tables[i]!='\0'; i++) {
			if (tables[i] == space[0])
				spaces++;
		}
		queries[q].involved_tables = malloc((spaces+1) * sizeof(int));
		queries[q].num_of_tables = spaces+1;
		token = strtok(tables, space);
		queries[q].involved_tables[0] = atoi(token);
		for (i=1; i<=spaces; i++) {
			token = strtok(NULL, space);
			queries[q].involved_tables[i] = atoi(token);
		}
		spaces = 0;
	// Reading predicates
		strcpy(official_predicates, predicates);
		while(official_predicates[0] != '\0') {
			dots = 0;
			strcpy(predicates, official_predicates);
			for (i=0; official_predicates[i]!='\0'; i++) {
				if (official_predicates[i] == dot[0])
					dots++;
				if (official_predicates[i] == ampersand[0])
					break;
			}
			if (dots == 1) {
				token = strtok(predicates, dot);
				queries[q].predicates_filter[queries[q].num_of_filters].table = atoi(token);
				for (i=0; official_predicates[i]!='\0'; i++) {
					if (official_predicates[i] == greater[0]){
						token = strtok(NULL, greater);
						queries[q].predicates_filter[queries[q].num_of_filters].symbol = greater[0];
						break;
					}
					else if (official_predicates[i] == lower[0]){
						token = strtok(NULL, lower);
						queries[q].predicates_filter[queries[q].num_of_filters].symbol = lower[0];
						break;
					}
					else if (official_predicates[i] == equal[0]){
						token = strtok(NULL, equal);
						queries[q].predicates_filter[queries[q].num_of_filters].symbol = equal[0];
						break;
					}
				}
				queries[q].predicates_filter[queries[q].num_of_filters].key = atoi(token);
				token = strtok(NULL,ampersand);
				queries[q].predicates_filter[queries[q].num_of_filters].number = atoi(token);
				queries[q].num_of_filters++;
			} else if (dots == 2) {
				token = strtok(predicates, dot);
				queries[q].predicates_smj[queries[q].num_of_smjs].table_1 = atoi(token);
				token = strtok(NULL, equal);
				queries[q].predicates_smj[queries[q].num_of_smjs].key_1 = atoi(token);
				token = strtok(NULL, dot);
				queries[q].predicates_smj[queries[q].num_of_smjs].table_2 = atoi(token);
				token = strtok(NULL, dot);
				queries[q].predicates_smj[queries[q].num_of_smjs].key_2 = atoi(token);
				queries[q].num_of_smjs++;
			}
			chars=0;
			for (i=0; official_predicates[i]!='\0'; i++) {
				if (official_predicates[i] == ampersand[0]) {
					stop = 1;
					break;
				}
				chars++;
			}
			if (stop == 0)
				break;
			else if (stop == 1)
				stop = 0;
			chars++;
			j = 0;
			for(i=chars; official_predicates[i]!='\0'; i++) {
				official_predicates[j] = official_predicates[i];
				j++;
			}
			official_predicates[j] = '\0';
			dots = 0;
		}
	// Reading sums
		spaces = 0;
		dots = 0;
		a = 0;
		for (i=0; sums[i]!='\0'; i++) {
			if (sums[i] == dot[0])
				dots++;
		}
		queries[q].result_sum = malloc((dots) * sizeof(int));
		queries[q].num_of_sums = dots;
		for(i=0; i<dots; i++) {
			strcpy(token, &sums[a]);
			queries[q].result_sum[i].table = atoi(token);
			a = a + 2;
			strcpy(token, &sums[a]);
			queries[q].result_sum[i].key = atoi(token);
			a = a + 2;
		}
		spaces = 0;
		token = "\n";
		predicates[0] = '\0';
		spaces = 0;
		q++;
		free(string);
	}
}
