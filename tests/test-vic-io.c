#include <stdio.h>
#include "munit.h"
#include "../src/vic.h"

#define DEBUG 1

int tests_passed = 0;
int tests_count = 0;

static char * test_vic_out()
{
    vic_out('a');
    char* a = vic_io_return();

    mu_assert(strlen(a) == 1);
    mu_assert(strcmp(a, "a") == 0);

    vic_io_clean();

    return 0;
}

static char * test_vic_print()
{
    vic_print("ahoj!");
    char* a = vic_io_return();

    mu_assert(strlen(a) == 5);
    mu_assert(strcmp(a, "ahoj!") == 0);

    vic_io_clean();

    return 0;
}

static char * test_vic_println()
{
    vic_println("ahoj!");
    char* a = vic_io_return();

    mu_assert(strlen(a) == 6);
    mu_assert(strcmp(a, "ahoj!\n") == 0);

    vic_io_clean();

    return 0;
}

static char * all_tests()
{

	mu_run_test(test_vic_out);
	mu_run_test(test_vic_print);
	mu_run_test(test_vic_println);
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

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
