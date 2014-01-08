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


static char * test_process()
{
	test_var = 0;
	char in[] = "call\n";

	int i;
	for(i = 0; i < strlen(in); i++){
		vic_process(in[i]);
	}
	mu_assert(test_var == 1);

	return 0;
}

static char * test_exec()
{
        test_var = 0;
        char* a = vic_exec("call;");
        mu_assert(test_var == 1);
        free(a);

        test_var = 0;
        a = vic_exec(";;;;;;;call;;;;;;;");
        mu_assert(test_var == 1);
        free(a);

        test_var = 0;
        a = vic_exec("    call;;;;;;;");
        mu_assert(test_var == 1);
        free(a);



	return 0;
}

static char * all_tests()
{

	vic_fn_add("call", &fn_call);

	mu_run_test(test_exec);
	mu_run_test(test_process);
	return 0;
}


int main(void)
{

        vic_init();
        vic_debug(1);

	char *result = all_tests();

	if (result == 0){
		printf("All tests passed!\n");
	} else {
		printf("%s\n", result);
	}

	printf("Status: %d from %d tests passed\n", tests_passed, tests_count);

	return 0;
}



