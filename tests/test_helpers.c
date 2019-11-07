#include "test_helpers.h"

void test_atouint64_t(void) {
	int result = 0;
	char *test_string_1 = "lld8235jdhg842";
	char *test_string_2 = "3548624853974258625shf";
	char *test_string_3 = "&%^Kjdfgn648535";
	char *test_string_4 = "497634 487";
	char *test_string_5 = "3467,28356.29ung934";
	
	if (atouint64_t(test_string_1) == 0)
		result++;
	if (atouint64_t(test_string_2) == 3548624853974258625)
		result++;
	if (atouint64_t(test_string_3) == 0)
		result++;
	if (atouint64_t(test_string_4) == 497634)
		result++;
	if (atouint64_t(test_string_5) == 3467)
		result++;
		
	printf("\n$$ File <<helpers.c>> Funtion <<atouint64_t>> test completed\n");
	if (result == 5)
		printf("$$	-->	Test passed	// Both valid and invalid input are treated accordingly\n");
	else if (result > 5)
		printf("$$	-->	Test failed	// Invalid input is considered valid\n");
	else if (result < 5)
		printf("$$	-->	Test failed	// Valid input is considered invalid\n");
}
