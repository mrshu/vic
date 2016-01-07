#include <stdio.h>
#include "munit.h"
#include "../src/vic.h"


int tests_passed = 0;
int tests_count = 0;

static char * test_process(void)
{
    char in[] = "call";

    int i;
    for(i = 0; i < strlen(in); i++){
        vic_process(in[i]);
    }
    mu_assert(strcmp(vic_buffer, in) == 0);

    return 0;
}

static char * test_process_backspace(void)
{
    char in[] = "call";

    int i;
    for(i = 0; i < strlen(in); i++){
        vic_process(in[i]);
    }
    for(i = 0; i < strlen(in) + 2; i++){
        vic_process((char)0x08); /* backspace */
    }
    for(i = 0; i < strlen(in); i++){
        vic_process(in[i]);
    }
    mu_assert(strcmp(vic_buffer, in) == 0);

    return 0;
}

static char * test_process_long_line(void)
{
    char in[VIC_BUFFER_SIZE] = {'a'};

    int i;
    for (i = 0; i < VIC_BUFFER_SIZE; i++){
        vic_process(in[i]);
    }
    vic_process('\0');
    mu_assert(strcmp(vic_buffer, in) == 0);

    return 0;
}

char last_printed;

void print(char c)
{
    putchar(c);
    last_printed = c;
}

static char * test_output(void)
{
    char in1[] = "Hello world\n";
    char in2 = 'X';

    vic_output_set(print);
    vic_print(in1);

    mu_assert(in1[strlen(in1)-1] == last_printed);

    vic_out(in2);

    mu_assert(in2 == last_printed);

    return 0;
}

static char * all_tests(void)
{
    mu_run_test(test_process);
    vic_buffer_clear();

    mu_run_test(test_process_backspace);
    vic_buffer_clear();

    mu_run_test(test_process_long_line);
    vic_buffer_clear();

    mu_run_test(test_output);

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
