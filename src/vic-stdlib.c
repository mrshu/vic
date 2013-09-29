#ifndef _VIC_STDLIB
#define _VIC_STDLIB

#include "vic.h"

void vic_func_plus()
{
        int argc;
        char** argv = vic__args(vic_buff, &argc);

        int i;
        int sum = 0;
        for(i = 0; i < argc; i++) {
                sum += atoi(argv[i]);
        }

        vic_print_int(sum);
        vic_out('\n');

        vic__args_clean(argv, argc);
}

void vic_func_minus()
{
        int argc;
        char** argv = vic__args(vic_buff, &argc);

        int i;
        int sum = 0;
        for(i = 0; i < argc; i++) {
                sum -= atoi(argv[i]);
        }

        vic_print_int(sum);
        vic_out('\n');

        vic__args_clean(argv, argc);
}

void vic_func_times()
{
        int argc;
        char** argv = vic__args(vic_buff, &argc);

        int i;
        int sum = 1;
        for(i = 0; i < argc; i++) {
                sum *= atoi(argv[i]);
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



#endif

