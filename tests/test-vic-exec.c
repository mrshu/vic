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

/*
  Testing intern functions
*/

#define BUFFER_LEN 128

char buffer[BUFFER_LEN] = {'\0'};
int buffer_i = 0;

void print(char c)
{
    if (buffer_i < BUFFER_LEN - 1) {
        buffer[buffer_i] = c;
        buffer_i++;
    }
}

static char * test_exec_set(void)
{
    int test_count = 5;

    char *in[] = {
        "  set  \n",
        "   set name  \n",
        " set name Peter \n",
        "set very_long_variable_name   very_long_variable_value \n",
        "  set age 7 \n"
    };
    const char *out[] = {
        vic_err_msg[VIC_ERR_INVALID_ARGS],
        vic_err_msg[VIC_ERR_INVALID_ARGS],
        vic_err_msg[VIC_ERR_NO],
        vic_err_msg[VIC_ERR_NO],
        vic_err_msg[VIC_ERR_NO]
    };

    vic_output_set(print);

    int test_i;
    for (test_i = 0; test_i < test_count; test_i++) {
        buffer_i = 0;
        int i;
        for (i = 0; i < strlen(in[test_i]); i++) {
            vic_process(in[test_i][i]);
        }
        buffer[buffer_i] = '\0';

        /*
        printf("in: %sout: %s\n", in[test_i], buffer);
        */

        mu_assert(strcmp(buffer, out[test_i]) == 0);
    }

    return 0;
}

static char *test_exec_set_get(void)
{
    int test_count = 12;

    char *in[] = {
        " set name Peter \n",
        "  set age 7 \n",
        " get    \n",
        "get age \n",
        " get name\n",
        "get   Peter \n",
        "set name Johny\n",
        "set age 1000000\n",
        "get name\n",
        "get age\n",
        "set too_long_var_name value\n",
        "get too_long_var_name\n"
    };
    const char *out[] = {
        vic_err_msg[VIC_ERR_NO],
        vic_err_msg[VIC_ERR_NO],
        vic_err_msg[VIC_ERR_INVALID_ARGS],
        "7\n",
        "Peter\n",
        vic_err_msg[VIC_ERR_INVALID_NAME],
        vic_err_msg[VIC_ERR_NO],
        vic_err_msg[VIC_ERR_NO],
        "Johny\n",
        "1000000\n",
        vic_err_msg[VIC_ERR_NO],
        "value\n"
    };

    vic_output_set(print);

    int test_i;
    for (test_i = 0; test_i < test_count; test_i++) {
        buffer_i = 0;
        int i;
        for (i = 0; i < strlen(in[test_i]); i++) {
            vic_process(in[test_i][i]);
        }
        buffer[buffer_i] = '\0';

        /*
        printf("in: %sout: %s\n", in[test_i], buffer);
        */

        mu_assert(strcmp(buffer, out[test_i]) == 0);
    }

    return 0;
}

static char * all_tests()
{
    mu_run_test(test_exec_func);
    mu_run_test(test_exec_par_func);
    mu_run_test(test_exec_bad_par_func);
    mu_run_test(test_exec_bad_par_func_2);
    mu_run_test(test_exec_set);
    mu_run_test(test_exec_set_get);

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
