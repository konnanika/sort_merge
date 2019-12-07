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
	int q = 0;
	char *string;
	char *token;
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
		//konnan
		for (i=1; i<=ampersands; i++){
			//konna

			for (i=0; token[i]!='\0'; i++) {
				if (token[i] == dot[0])
					dots++;
			}   
			if (dots == 1) {
				temp = strtok(token, dot);
				queries[q].predicates_filter[queries[q].num_of_filters].table = atoi(temp);
	//			temp = strtok(NULL, );
	//			queries[q].predicates_filter[queries[q].num_of_filters].table = atoi(temp);
				queries[q].num_of_filters++;
			}
			else if(dots == 2){
				//konnan
				temp = strtok(token, dot);
				queries[q].predicates_smj[queries[q].num_of_smjs].table_1 = atoi(temp);
				queries[q].num_of_smjs++;
			}
			//konnan
			token = strtok(NULL, ampersand);
		}
	// Reading sums
		for (i=0; sums[i]!='\0'; i++) {
			if (sums[i] == space[0])
				spaces++;
		}
		token = strtok(sums, space);
		queries[q].result_sum[queries[q].num_of_sums].table = atoi(token);
		for (i=1; i<=spaces; i++) {
			token = strtok(NULL, space);
			queries[q].result_sum[queries[q].num_of_sums].table = atoi(token);
			queries[q].num_of_sums++;
		}
		spaces = 0;	
		//konnan
		q++;
		free(string);
	}
}




