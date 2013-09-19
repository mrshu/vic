#include <stdio.h>
#include "munit.h"

#define DEBUG 1
#include "../src/vic.h"


int tests_passed = 0;
int tests_count = 0;

int test_var = 0;

static char * test_simple_replace()
{
    char in[] = "$hello\0";
    char* out = vic_var_replace(in);
    mu_assert(strcmp(out, "hello world") == 0);

    vic_var_set("a", "hey");

    char in_a[] = "a=$a\0";
    char* out_a = vic_var_replace(in_a);
    mu_assert(strcmp(out_a, "a=hey") == 0);

    dprint_str(out_a);

    vic_var_set("name", "John");

    char in_b[] = "Hey $name!\0";
    char* out_b = vic_var_replace(in_b);
    mu_assert(strcmp(out_b, "Hey John!") == 0);

    dprint_str(out_b);

    vic_var_set("surname", "Travolta");
    char in_c[] = "Hey $name $surname!\0";
    char* out_c = vic_var_replace(in_c);
    mu_assert(strcmp(out_c, "Hey John Travolta!") == 0);

    dprint_str(out_c);

    vic_var_set("full_name", "John Travolta");
    char in_d[] = "Hey $full_name!\0";
    char* out_d = vic_var_replace(in_d);
    mu_assert(strcmp(out_d, "Hey John Travolta!") == 0);

    dprint_str(out_d);

    char in_e[] = "My name is $surname, $name $surname!\0";
    char* out_e = vic_var_replace(in_e);
    mu_assert(strcmp(out_e, "My name is Travolta, John Travolta!") == 0);

    dprint_str(out_e);

    return 0;
}

static char * all_tests()
{
    vic_var_set("hello", "hello world");

    mu_run_test(test_simple_replace);
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



