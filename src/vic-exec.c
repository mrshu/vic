#ifndef _VIC_EXEC
#define _VIC_EXEC

#include "vic.h"

#include <ctype.h>
#include <string.h>

char *vic_args_s = NULL;

int vic_exec(char *input)
{
    int start = 0, end;
    /* find start of func name */
    while (isspace(input[start])) {
        start++;
    }
    
    /* end of line */
    if (input[start] == '\0') {
        return VIC_ERR_NO;
    }

    end = start;
    /* find end of func name */
    while (isspace(input[end]) == 0) {
        /* end of line */
        if (input[end] == '\0') {
            break;
        }
        end++;
    }
    input[end] = '\0';

    vic_args_s = input + end + 1;
    int error = vic_fn_call(input + start);
    vic_args_s = NULL;

    return error;
}

#endif

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
