#include <stdio.h>
#include "munit.h"
#include "../src/vic.h"


int tests_passed = 0;
int tests_count = 0;

int test_var = 0;

void fn_call()
{
	test_var = 1;
}


static char * test_call()
{
	vic_fn_call("call");
	mu_assert(test_var == 1);
	return 0;
}

static char * all_tests()
{

	vic_fn_add("call", &fn_call);

	mu_run_test(test_call);
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



