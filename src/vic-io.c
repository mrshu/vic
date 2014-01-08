#ifndef _VIC_IO
#define _VIC_IO

#include "vic.h"

#include <stdlib.h>
#include <stdint.h>

char* vic_output;
static uint8_t vic_output_len = 0;

void vic_out(char x)
{
    if (vic_output_len == 0) {
        vic_output = (char *) malloc( (vic_output_len + 1) * sizeof(char));
    } else {
        vic_output = (char *)
                realloc(vic_output,
                        (vic_output_len + 1) * sizeof(char)
                );
    }
    vic_output[vic_output_len++] = x;
}

void vic_print(char *x)
{

    do {
        vic_out(*x);
        x++;
    } while (*x != '\0');

}

void vic_println(char *x)
{
    vic_print(x);
    vic_out('\n');

}

char* vic_io_return()
{
    vic_out('\0');
    dprint_int(vic_output);
    return vic_output;
}

void vic_io_clean()
{
    free(vic_output);
    vic_output = NULL;
    vic_output_len = 0;
}



#endif

