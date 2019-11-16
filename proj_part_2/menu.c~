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

void queries_menu (query **queries) {
// Variables
	int i = 0;
	char *string;
	char *token;
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
	char enter[] = "\n";

// Menu Interface
	printf("Please type your queries :\n");
	while(1) {
		string = (char *)malloc(stringsize * sizeof(char));
		printf("	-->	");
		characters = getline(&string, &stringsize, stdin);
		if (string[0] == 'F') {
			free(string);
			break;
		}
		token = strtok(string, pipe);
		strcpy(tables, token);
		token = strtok(NULL, pipe);
		strcpy(predicates, token);
		token = strtok(NULL, enter);
		strcpy(sums, token);
		printf("\ntables involved : |%s|\npredicates : |%s|\nsums : |%s|\n", tables, predicates, sums);
		free(string);
	}
}

















