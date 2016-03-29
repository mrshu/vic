#include <stdio.h>
#include "munit.h"
#include "../src/vic.h"

int tests_passed = 0;
int tests_count = 0;

int test_var = 0;

static void test_func(void)
{
    test_var++;
}

static void test_func2(void)
{
    test_var += 2;
}


static char * test_fn_add_overflow(void)
{
    char name[VIC_FUNC_NAME_LEN + 1] = {0x01};
    name[VIC_FUNC_NAME_LEN] = '\0';

    int i, j;
    for (i = 0; i < VIC_FUNCS_COUNT; i++) {
        /* create new name */
        for (j = 0; j < VIC_FUNC_NAME_LEN; j++) {
            if (name[j] < 0xFF) {
                name[j]++;
                break;
            }
            name[j] = 0x01;
        }
        vic_fn_add(name, test_func);
    }

    mu_assert(vic_fn_add("a", test_func) != VIC_ERR_NO);

    return 0;
}

static char * test_fn_add_long_name(void)
{
    char true_name[VIC_FUNC_NAME_LEN + 1] = {'a'};
    char name[VIC_FUNC_NAME_LEN + 3] = {'a'};
    name[VIC_FUNC_NAME_LEN + 2] = '\0';
    true_name[VIC_FUNC_NAME_LEN] = '\0';

    test_var = 0;
    vic_fn_add(name, test_func);
    vic_fn_call(true_name);

    mu_assert(test_var == 1);

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

static char * test_fn_call_invalid_name(void)
{
    test_var = 0;
    vic_fn_add("name", test_func);

    mu_assert(vic_fn_call("wrongname") == VIC_ERR_INVALID_NAME);
    mu_assert(test_var == 0);

    return 0;
}

static char * test_fn_rm(void)
{
    vic_fn_add("name", test_func);
    vic_fn_add("name2", test_func);
    vic_fn_add("name3", test_func);

    mu_assert(vic_fn_rm("name2") == VIC_ERR_NO);
    mu_assert(vic_fn_rm("name2") == VIC_ERR_INVALID_NAME);

    return 0;
}

static char * test_fn_overwrite(void)
{
    test_var = 0;
    vic_fn_add("name", test_func);
    vic_fn_call("name");
    vic_fn_add("name", test_func2);

    mu_assert(vic_fn_call("name") == VIC_ERR_NO);
    mu_assert(test_var == 3);

    return 0;
}

static char * all_tests(void)
{
    mu_run_test(test_fn_add_overflow);
    vic_funcs_clear();

    mu_run_test(test_fn_add_long_name);
    vic_funcs_clear();

    mu_run_test(test_fn_call);
    vic_funcs_clear();

    mu_run_test(test_fn_call_invalid_name);
    vic_funcs_clear();

    mu_run_test(test_fn_rm);
    vic_funcs_clear();

    mu_run_test(test_fn_overwrite);

    return 0;
}


int main(void)
{
    vic_init(NULL);

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
