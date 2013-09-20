#include <stdio.h>
#include "munit.h"
#include "../src/vic.h"

#define DEBUG 1

int tests_passed = 0;
int tests_count = 0;

static char * test_simple_exec()
{

    char in[] = "echo ahoj;";
    dprint_str(in);
    char* output = vic_exec(in);

    mu_assert(strlen(output) == 5);
    mu_assert(strcmp(output, "ahoj\n") == 0);

    vic_io_clean();
    return 0;
}


static char * all_tests()
{
    vic_init();

	mu_run_test(test_simple_exec);
	return 0;
}


int main(void)
{
	char *result = all_tests();

	if (result == 0){
		printf("All tests passed!\n");
	} else {
		printf("%s\n", result);
	}

	printf("Status: %d from %d tests passed\n", tests_passed, tests_count);

	return 0;
}



