#ifndef _VIC_STDLIB
#define _VIC_STDLIB

#include "vic.h"

void vic_func_plus()
{
        int argc;
        uint8_t ebits;
        char** argv = vic__args_ebits(vic_buff, &argc, &ebits);

        int i;
        int sum = 0;
        for(i = 0; i < argc; i++) {
                // 1 << i is used here to check whether the argument has an ebit set
                if ((ebits & (1 << i))) {
                    char* out;
                    vic_exec_cstr(argv[i], out);

                    sum += atoi(out);

                    free(out);
                } else {
                    sum += atoi(argv[i]);
                }
        }

        vic_print_int(sum);
        vic_out('\n');

        vic__args_clean(argv, argc);
}

void vic_func_minus()
{
        int argc;
        uint8_t ebits;
        char** argv = vic__args_ebits(vic_buff, &argc, &ebits);

        int i;
        int sum = 0;
        for(i = 0; i < argc; i++) {
                // 1 << i is used here to check whether the argument has an ebit set
                if ((ebits & (1 << i))) {
                    char* out;
                    vic_exec_cstr(argv[i], out);

                    sum -= atoi(out);

                    free(out);
                } else {
                    sum -= atoi(argv[i]);
                }
        }

        vic_print_int(sum);
        vic_out('\n');

        vic__args_clean(argv, argc);
}

void vic_func_times()
{
        int argc;
        uint8_t ebits;
        char** argv = vic__args_ebits(vic_buff, &argc, &ebits);

        int i;
        int sum = 1;
        for(i = 0; i < argc; i++) {
                // 1 << i is used here to check whether the argument has an ebit set
                if ((ebits & (1 << i))) {
                    char* out;
                    vic_exec_cstr(argv[i], out);

                    sum *= atoi(out);

                    free(out);
                } else {
                    sum -= atoi(argv[i]);
                }
        }

        vic_print_int(sum);
        vic_out('\n');

        vic__args_clean(argv, argc);
}

void vic_func_division()
{
        int argc;
        char** argv = vic__args(vic_buff, &argc);

        if (argc >= 1) {
                int i;
                int sum = atol(argv[0]);
                for(i = 1; i < argc; i++) {
                        int j = atoi(argv[i]);

                        if (j != 0) {
                                sum /= j;
                        } else {
                                vic_println("NaN");
                                vic__args_clean(argv, argc);
                                return;
                        }
                }

                vic_print_int(sum);
                vic_out('\n');

        }

        vic__args_clean(argv, argc);
}

void vic_func_modulo()
{
        int argc;
        char** argv = vic__args(vic_buff, &argc);

        if (argc >= 1) {
                int i;
                int sum = atol(argv[0]);
                for(i = 1; i < argc; i++) {
                        sum %= atoi(argv[i]);
                }

                vic_print_int(sum);
                vic_out('\n');

        }

        vic__args_clean(argv, argc);
}

void vic_func_equals()
{
        int argc;
        char** argv = vic__args(vic_buff, &argc);

        if (argc >= 1) {
                char* first = argv[0];
                int i;
                for(i = 1; i < argc; i++) {
                        if (strcmp(first, argv[i]) != 0) {
                                vic_println("F");
                                vic__args_clean(argv, argc);
                                return;
                        }
                }

                vic_println("T");
        }

        vic__args_clean(argv, argc);
}


void vic_func_if()
{
///     int argc;
///     char** argv = vic__args(vic_buff, &argc);


///     if (argc == 2) {
///             char* ret = vic_exec(argv[0]);
///             if (strcmp(ret, "F") != 0 || strlen(ret) != 0) {
///                     char* out = vic_exec(argv[1]);
///                     vic_print(out);
///             }
///     } else if (argc >= 3) {
///             char* ret = vic_exec(argv[0]);
///             vic_sys_println(argv[0]);
///             char* out;
///             if (strcmp(ret, "F") != 0 || strlen(ret) != 0) {
///                     vic_io_clean();
///                     out = vic_exec(argv[1]);
///             } else {
///                     vic_io_clean();
///                     out = vic_exec(argv[2]);
///             }
///             vic_print(out);
///             vic_io_clean();
///     }

///     vic__args_clean(argv, argc);
}


#endif

