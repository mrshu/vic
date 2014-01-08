#include <stdio.h>
#include "munit.h"
#include "../src/vic.h"

#define DEBUG 1

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

static char * test_set()
{
    char in[] = "set x (echo 'a');";
    char* output = vic_exec(in);
    mu_assert(strcmp(vic_var_get("x"), "a") == 0);

    free(output);
    return 0;
}

static char * test_compute()
{
    char in[] = "+ 2 3;";
    char* output = vic_exec(in);
    dprint_str(output);

    mu_assert(1 == 0);

    free(output);
    return 0;

}


static char * all_tests()
{

    vic_init();
    vic_debug(1);

    vic_fn_add("call", &fn_call);

    mu_run_test(test_call);
    mu_run_test(test_set);
    mu_run_test(test_compute);
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



