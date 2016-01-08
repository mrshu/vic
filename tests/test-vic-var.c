#include <stdio.h>
#include <math.h>
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

static char * test_var_bind_uint(void)
{
    char *var_name = "num";
    char *str_value_8 = "255";
    char *str_value_16 = "65535";
    uint8_t value_8;
    uint16_t value_16;

    vic_var_set(var_name, str_value_8);
    vic_var_bind(var_name, &value_8, VIC_VAR_UINT8);
    mu_assert(value_8 == atol(str_value_8));

    vic_var_set(var_name, str_value_16);
    vic_var_bind(var_name, &value_16, VIC_VAR_UINT16);
    mu_assert(value_16 == atol(str_value_16));

    str_value_8 = "0";
    str_value_16 = "0";

    vic_var_set(var_name, str_value_8);
    vic_var_bind(var_name, &value_8, VIC_VAR_UINT8);
    mu_assert(value_8 == atol(str_value_8));

    vic_var_set(var_name, str_value_16);
    vic_var_bind(var_name, &value_16, VIC_VAR_UINT16);
    mu_assert(value_16 == atol(str_value_16));

    return 0;
}

static char * test_var_bind_int(void)
{
    char *var_name = "num";
    char *str_value_8 = "127";
    char *str_value_16 = "32767";
    int8_t value_8;
    int16_t value_16;

    vic_var_set(var_name, str_value_8);
    vic_var_bind(var_name, &value_8, VIC_VAR_INT8);
    mu_assert(value_8 == atol(str_value_8));

    vic_var_set(var_name, str_value_16);
    vic_var_bind(var_name, &value_16, VIC_VAR_INT16);
    mu_assert(value_16 == atol(str_value_16));

    str_value_8 = "-128";
    str_value_16 = "-32768";

    vic_var_set(var_name, str_value_8);
    vic_var_bind(var_name, &value_8, VIC_VAR_INT8);
    mu_assert(value_8 == atol(str_value_8));

    vic_var_set(var_name, str_value_16);
    vic_var_bind(var_name, &value_16, VIC_VAR_INT16);
    mu_assert(value_16 == atol(str_value_16));

    return 0;
}

static char * test_var_bind_float(void)
{
    char *var_name = "num";
    char *str_value = "12.345";
    float value;

    vic_var_set(var_name, str_value);
    vic_var_bind(var_name, &value, VIC_VAR_FLOAT);
    mu_assert(fabs(value - atof(str_value)) < 0.001f);

    return 0;
}

static char * all_tests(void)
{
    mu_run_test(test_var_basic);
    vic_vars_clear();

    mu_run_test(test_var_bind_uint);
    vic_vars_clear();

    mu_run_test(test_var_bind_int);
    vic_vars_clear();

    mu_run_test(test_var_bind_float);

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
