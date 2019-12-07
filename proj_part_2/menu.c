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

void queries_menu (query queries[MAX_NUM_OF_QUERIES]) {
// Variables
	int i = 0;
	int j = 0;
	int q = 0;
	char *string;
	char *token = '\0';
	char *temp;
	char tables[STRING_LENGTH];
	char predicates[STRING_LENGTH];
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
			free(string);
			break;
		}
		init_query(queries[q]);
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
		token = strtok(tables, space);
		queries[q].involved_tables[0] = atoi(token);
		for (i=1; i<=spaces; i++) {
			token = strtok(NULL, space);
			queries[q].involved_tables[i] = atoi(token);
		}
		spaces = 0;
	// Reading predicates
		for (i=0; predicates[i]!='\0'; i++) {
			if (predicates[i] == ampersand[0])
				ampersands++;
		}
		token = strtok(predicates, ampersand);
		//Looping for all ampersands plus one
		for (j=1; j<=ampersands; j++){
			printf("exoyme epanalipsis = %d\n",j);
			printf("ampersands = %d\n",ampersands);
			printf("token = %s in %d\n",token,j);
			//Find all the dots to seperate the filters and smjs
			for (i=0; token[i]!='\0'; i++) {
				if (token[i] == dot[0])
					dots++;
<<<<<<< HEAD
			}   
=======
			}
			printf("dots = %d in epanalipsi = %d\n",dots, j);
			temp = malloc(sizeof(*token));
			strcpy(temp,token);
			// When dots = 1 then is filter
>>>>>>> 4fcb52a3d767e8a414d9ab7dd5339ade3ccfdceb
			if (dots == 1) {
				temp = strtok(temp, dot);
				queries[q].predicates_filter[queries[q].num_of_filters].table = atoi(temp);
				//If the symbol is the greater or the lower
				for (i=0; token[i]!='\0'; i++) {
					if (token[i] == greater[0]){
						temp = strtok(NULL, greater);
						queries[q].predicates_filter[queries[q].num_of_filters].symbol = greater[0];
					}
					else if (token[i] == lower[0]){
						temp = strtok(NULL, lower);
						queries[q].predicates_filter[queries[q].num_of_filters].symbol = lower[0];
					}
					else if (token[i] == equal[0]){
						temp = strtok(NULL, equal);
						queries[q].predicates_filter[queries[q].num_of_filters].symbol = equal[0];
					}
				}
				queries[q].predicates_filter[queries[q].num_of_filters].key = atoi(temp);
				temp = strtok(NULL,dot);
				queries[q].predicates_filter[queries[q].num_of_filters].number = atoi(temp);
				queries[q].num_of_filters++;
			}
			// When dots = 2 then is smj
			else if(dots == 2){
				//Take the first table with the key (for joing with the second)
				temp = strtok(temp, dot);
				queries[q].predicates_smj[queries[q].num_of_smjs].table_1 = atoi(temp);
<<<<<<< HEAD
=======
				temp = strtok(NULL, equal);
				queries[q].predicates_smj[queries[q].num_of_smjs].key_1 = atoi(temp);
				//Take the second table with the key
				temp = strtok(NULL, dot);
				queries[q].predicates_smj[queries[q].num_of_smjs].table_2 = atoi(temp);
				temp = strtok(NULL, dot);
				queries[q].predicates_smj[queries[q].num_of_smjs].key_2 = atoi(temp);
<<<<<<< HEAD
=======

>>>>>>> 4fcb52a3d767e8a414d9ab7dd5339ade3ccfdceb
>>>>>>> 5a758856bec12dd0fee8ce538d1448a98f0d1c9b
				queries[q].num_of_smjs++;
			}
			printf("num_of_filters = %d\n",queries[q].num_of_filters);
			printf("num_of_smjs = %d\n",queries[q].num_of_smjs);
			token = strtok(NULL, ampersand);
			dots = 0;
		}
	// Reading sums
		for (i=0; sums[i]!='\0'; i++) {
			if (sums[i] == space[0])
				spaces++;
		}
		token = strtok(sums, space);
		// Looping until find all the sums for spaces plus one
		for (i=1; i<=spaces; i++) {
			temp = strtok(token,dot);
			queries[q].result_sum[queries[q].num_of_sums].table = atoi(temp);
			temp = strtok(NULL,dot);
			queries[q].result_sum[queries[q].num_of_sums].key = atoi(temp);

			queries[q].num_of_sums++;
			token = strtok(NULL, space);
		}
		spaces = 0;	
		q++;
		free(temp);
		//free(token);
		free(string);
	}
}




