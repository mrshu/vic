/* file: minunit.h */
#define STR(x) #x
#define TOSTR(x) STR(x)
#define mu_assert(test) do { tests_count++;  if (!(test)) {\
	return __FILE__ ":" TOSTR(__LINE__) " - assert failed -> " TOSTR(test) " \n"; } tests_passed++;} while (0)

#define mu_run_test(test) do { char *message = test();  \
	if (message) { return message; } } while (0)

extern int tests_count;
extern int tests_passed;

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
