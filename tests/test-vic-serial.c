#include <stdio.h>
#include "munit.h"
#include "../src/vic.h"


int tests_passed = 0;
int tests_count = 0;

static char * test_process()
{
	char in[] = "call\n";

	int i;
	for(i = 0; i < strlen(in); i++){
		vic_process(in[i]);
	}
	mu_assert(strcmp(vic_buffer, in) == 0);

	return 0;
}


static char * all_tests()
{


	mu_run_test(test_process);
	return 0;
}


int main(void)
{

        vic_init();

	char *result = all_tests();

	if (result == 0){
		printf("All tests passed!\n");
	} else {
		printf("%s\n", result);
	}

	printf("Status: %d from %d tests passed\n", tests_passed, tests_count);

	return 0;
}



