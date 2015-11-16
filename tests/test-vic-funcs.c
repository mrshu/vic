#include <stdio.h>
#include "munit.h"
#include "../src/vic.h"

int tests_passed = 0;
int tests_count = 0;

int test_var = 0;

void test_func(void)
{
    test_var++;
}

static char * test_fn_add_easy(void)
{
    vic_fn_add("test", test_func);

    mu_assert(strcmp(vic_funcs[0].name, "test") == 0);
    mu_assert(vic_funcs[0].p_func == &test_func);

    return 0;
}

static char * test_fn_add_overflow(void)
{
    int i;
    for (i = 0; i < VIC_FUNCS_COUNT; i++) {
        vic_fn_add("test", test_func);
    }

    mu_assert(vic_fn_add("a", test_func) != VIC_NO_ERR);

    return 0;
}

static char * test_fn_add_long_name(void)
{
    char true_name[VIC_FUNC_NAME_LEN + 1] = {'a'};
    char name[VIC_FUNC_NAME_LEN + 3] = {'a'};
    name[VIC_FUNC_NAME_LEN + 2] = '\0';
    true_name[VIC_FUNC_NAME_LEN] = '\0';

    vic_fn_add(name, test_func);

    mu_assert(strcmp(vic_funcs[0].name, true_name) == 0);

    return 0;
}

static char * test_fn_call(void)
{
    test_var = 0;
    char *name = "calltest";
    vic_fn_add(name, test_func);
    vic_fn_call(name);
    vic_fn_call(name);
    vic_fn_call(name);

    mu_assert(test_var == 3);

    return 0;
}

static char * test_fn_call_wrong_name(void)
{
    test_var = 0;
    vic_fn_add("name", test_func);

    mu_assert(vic_fn_call("wrongname") == VIC_WRONG_FUNC_NAME);
    mu_assert(test_var == 0);

    return 0;
}

static char * all_tests(void)
{
    mu_run_test(test_fn_add_overflow);
    vic_funcs_clear();
    mu_run_test(test_fn_add_easy);
    vic_funcs_clear();
    mu_run_test(test_fn_add_long_name);
    vic_funcs_clear();
    mu_run_test(test_fn_call);
    vic_funcs_clear();
    mu_run_test(test_fn_call_wrong_name);

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

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
