#include <stdio.h>
#include "munit.h"
#include "../src/vic.h"

#define DEBUG 1

int tests_passed = 0;
int tests_count = 0;

static char * test_simple_exec()
{

    char in[] = "echo ahoj;";
    char* output = vic_exec(in);

    mu_assert(strlen(output) == 5);
    mu_assert(strcmp(output, "ahoj\n") == 0);

    vic_io_clean();
    return 0;
}

static char * test_complicated_exec()
{

    char in[] = "echo ahoj;set f 20;echo fero;echo $f;";
    char* output = vic_exec(in);

    mu_assert(strlen(output) == 13);
    mu_assert(strcmp(output, "ahoj\nfero\n20\n") == 0);

    vic_io_clean();
    return 0;
}


static char * all_tests()
{
    vic_init();

	mu_run_test(test_simple_exec);
	mu_run_test(test_complicated_exec);
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



