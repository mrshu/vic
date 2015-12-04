#ifndef _VIC_EXEC
#define _VIC_EXEC

#include "vic.h"

#include <ctype.h>
#include <string.h>

void vic_exec(char *input)
{
    int start = 0, end;
    /* find start of func name */
    while (isspace(input[start])) {
        start++;
    }
    
    /* end of line */
    if (input[start] == '\0') {
        return;
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

    vic_fn_call(input + start);
}

#endif
