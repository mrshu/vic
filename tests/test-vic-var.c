#include <stdio.h>
#include "munit.h"
#include "../src/vic.h"

int tests_passed = 0;
int tests_count = 0;

static char * test_var_basic(void)
{
    char *var_name1 = "name";
    char *var_name2 = "age";
    char *right_value1 = "John";
    int age = 17;
    int *right_value2 = &age;

    mu_assert(vic_var_set(var_name1, right_value1) == VIC_ERR_NO);
    mu_assert(vic_var_set(var_name2, (char *)right_value2) == VIC_ERR_NO);

    char *value1;
    int *value2;

    vic_var_get(var_name1, &value1);
    vic_var_get(var_name2, (char **)(&value2));

    mu_assert(strcmp(value1, right_value1) == 0);
    mu_assert(*value2 == *right_value2);

    return 0;
}

static char * all_tests(void)
{
    mu_run_test(test_var_basic);

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
