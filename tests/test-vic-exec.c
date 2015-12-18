#include <stdio.h>
#include "munit.h"
#include "../src/vic.h"

int tests_passed = 0;
int tests_count = 0;

int test_var;
int parameters;

static void test_func(void)
{
    test_var++;
}

static void test_par(void)
{
    int a, b;
    if ((parameters = vic_args("%d %d", &a, &b)) == 2) {
        test_var = a + b;
    }
}

static char * test_exec_func(void)
{
    test_var = 0;
    char in[] = "test\n     test   \nmistake\n\tanother_test\n";
    vic_fn_add("test", test_func);
    vic_fn_add("another_test", test_func);

    int i;
    for (i = 0; i < strlen(in); i++) {
        vic_process(in[i]);
    }

    mu_assert(test_var == 3);

    return 0;
}

static char * test_exec_par_func(void)
{
    test_var = 0;
    char in[] = "test_par  3 4  \n  test_par   3 4 5 6 \n";
    vic_fn_add("test_par", test_par);

    int i;
    for (i = 0; i < strlen(in); i++) {
        vic_process(in[i]);
        if (in[i] == '\n') {
            mu_assert(parameters == 2);
            mu_assert(test_var == 7);
        }
    }

    return 0;
}

static char * test_exec_bad_par_func(void)
{
    test_var = 0;
    char in[] = "test_par  3   \n";
    vic_fn_add("test_par", test_par);

    int i;
    for (i = 0; i < strlen(in); i++) {
        vic_process(in[i]);
    }

    mu_assert(parameters == 1);
    mu_assert(test_var == 0);

    return 0;
}

static char * test_exec_bad_par_func_2(void)
{
    test_var = 0;
    char in[] = "test_par     \ntest_par f g\n";
    vic_fn_add("test_par", test_par);

    int i;
    for (i = 0; i < strlen(in); i++) {
        vic_process(in[i]);
        if (in[i] == '\n') {
            mu_assert((parameters == 0) || (parameters == EOF));
            mu_assert(test_var == 0);
        }
    }

    return 0;
}

static char * all_tests()
{
    mu_run_test(test_exec_func);
    mu_run_test(test_exec_par_func);
    mu_run_test(test_exec_bad_par_func);
    mu_run_test(test_exec_bad_par_func_2);

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
