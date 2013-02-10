#include <stdio.h>
#include "minunit.h"

int tests_passed = 0;
int tests_count = 0;

int foo = 7;
int bar = 4;

static char * test_foo() {
    mu_assert(foo == 3);
    return 0;
}

static char * test_bar() {
    mu_assert(bar == 4);
    return 0;
}

static char * all_tests() {
    mu_run_test(test_foo);
    mu_run_test(test_bar);
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();
    if (result == 0){
        printf("ALL TESTS PASSED\n");
    } else {
    	printf("%s\n", result);
    }
    
    printf("Tested/Passed: %d/%d\n", tests_count, tests_passed);

    return result != 0;
}
