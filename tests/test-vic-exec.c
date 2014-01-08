#include <stdio.h>
#include "munit.h"
#include "../src/vic.h"

#define DEBUG 1

int tests_passed = 0;
int tests_count = 0;

static char * test_simple_exec()
{

    char in[] = "echo ahoj;";
    char* output = vic_exec(in);

    mu_assert(strlen(output) == 5);
    mu_assert(strcmp(output, "ahoj\n") == 0);

    free(output);
    return 0;
}

static char * test_complicated_exec()
{

    char in[] = "echo ahoj;set f 20;echo fero;echo $f;";
    char* output = vic_exec(in);

    dprint_str(output);
    mu_assert(strlen(output) == 13);
    mu_assert(strcmp(output, "ahoj\nfero\n20\n") == 0);

    free(output);
    return 0;
}

static char * test_simple_eval_replace()
{

    char in[] = "echo `echo fero`;";
    char* output = vic_replace_evals(in);
    dprint_str(output);

    mu_assert(strlen(output) == 11);
    mu_assert(strcmp(output, "echo fero\n;") == 0);

    free(output);
    return 0;
}

static char * test_args()
{

    char in[] = "echo 'A B' \"C\" 'D \"E\"' \"F 'G'\"";
    int argc = 0;
    char **argv = vic__args(in, &argc);

    mu_assert(argc == 5);
    mu_assert(strcmp(argv[0], "echo") == 0);
    mu_assert(strcmp(argv[1], "A B") == 0);
    mu_assert(strcmp(argv[2], "C") == 0);
    mu_assert(strcmp(argv[3], "D \"E\"") == 0);
    mu_assert(strcmp(argv[4], "F 'G'") == 0);

  //for (j = 0; j < argc; j++) {
  //    free(argv[j]);
  //}
  //free(argv);

    vic__args_clean(argv, argc);
    return 0;
}

static char * test_args_advanced()
{

    char in[] = "echo 'hi'   there \"I\"   am 'Richard II.'";
    int argc = 0;
    char **argv = vic__args(in, &argc);

    mu_assert(argc == 6);
    mu_assert(strcmp(argv[0], "echo") == 0);
    mu_assert(strcmp(argv[1], "hi") == 0);
    mu_assert(strcmp(argv[2], "there") == 0);
    mu_assert(strcmp(argv[3], "I") == 0);
    mu_assert(strcmp(argv[4], "am") == 0);
    mu_assert(strcmp(argv[5], "Richard II.") == 0);

    vic__args_clean(argv, argc);


    return 0;
}

static char * test_args_ebits()
{

    char in[] = "set y (+ $x 1)";
    int argc = 0;
    uint8_t ebits;
    char **argv = vic__args_ebits(in, &argc, &ebits);

    dprint_int(ebits);
    mu_assert(argc == 3);
    mu_assert(strcmp(argv[0], "set") == 0);
    mu_assert(strcmp(argv[1], "y") == 0);
    mu_assert(strcmp(argv[2], "+ $x 1") == 0);

    mu_assert((ebits & 2) == 0);
    mu_assert((ebits & 1) == 0);
    mu_assert(ebits & 4);

    vic__args_clean(argv, argc);
    return 0;
}


static char * all_tests()
{
    vic_init();
    vic_debug(1);

	mu_run_test(test_simple_exec);
    mu_run_test(test_complicated_exec);

    mu_run_test(test_simple_eval_replace);

    mu_run_test(test_args);
    mu_run_test(test_args_advanced);
    mu_run_test(test_args_ebits);
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



