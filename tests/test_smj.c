#include "test_smj.h"

int main(int argc, char **argv) {
// Variables
int result = 0;
// Arguments
	if (strcmp(argv[1], "smj.c") == 0) {
		test_parse_input_file(NULL, "tesrelA", "tesrelB");
		test_atouint64_t();		
	} else if (strcmp(argv[1], "parser.c") == 0) {
		test_parse_input_file(NULL, "tesrelA", "tesrelB");		
	} else if (strcmp(argv[1], "parse_input_file") == 0) {
		test_parse_input_file(NULL, "tesrelA", "tesrelB");
	} else 	if (strcmp(argv[1], "helpers.c") == 0) {
		test_atouint64_t();
	} else 	if (strcmp(argv[1], "atouint64_t") == 0) {
		test_atouint64_t();
/*	} else 	if (strcmp(argv[1], "test_parser.c") == 0) {
		test_parse_input_file(NULL, "tesrelA", "tesrelB");
	} else 	if (strcmp(argv[1], "test_parser.c") == 0) {
		test_parse_input_file(NULL, "tesrelA", "tesrelB");
	} else 	if (strcmp(argv[1], "test_parser.c") == 0) {
		test_parse_input_file(NULL, "tesrelA", "tesrelB");
	} else 	if (strcmp(argv[1], "test_parser.c") == 0) {
		test_parse_input_file(NULL, "tesrelA", "tesrelB");
	} else 	if (strcmp(argv[1], "test_parser.c") == 0) {
		test_parse_input_file(NULL, "tesrelA", "tesrelB");
	} else 	if (strcmp(argv[1], "test_parser.c") == 0) {
		test_parse_input_file(NULL, "tesrelA", "tesrelB");
*/	} else {
		printf("$$ Invalid Arguments\n$$ Please rerun ./test_smj <name_of_function or name_of_file.c>\n");
	}
	printf("\n");
}
