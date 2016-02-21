#ifndef _VIC_SERIAL
#define _VIC_SERIAL

#include "vic.h"

#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>


uint8_t vic_buffer_in_len = 0;
char vic_buffer_in[VIC_BUFFER_IN_SIZE + 1] = {'\0'};
char vic_buffer_out[VIC_BUFFER_OUT_SIZE + 1] = {'\0'};

void (*vic_output_func)(char) = NULL;

void vic_out(char c)
{
    if (vic_output_func != NULL) {
        vic_output_func(c);
    }
}

void vic_print(const char *s)
{
    if (vic_output_func != NULL) {
        while (*s != '\0') {
            vic_output_func(*s);
            s++;
        }
    }
}

void vic_print_err(uint8_t id)
{
    const char *err_msg = pgm_read_word(&vic_err_msg[id]);
    strncpy_P(vic_buffer_out, err_msg, VIC_BUFFER_OUT_SIZE);
    vic_print(vic_buffer_out);
}

void vic_buffer_clear(void)
{
    memset(vic_buffer_in, '\0', VIC_BUFFER_IN_SIZE);
    vic_buffer_in_len = 0;
}

void vic_buffer_append(char i)
{
    if (vic_buffer_in_len < VIC_BUFFER_IN_SIZE)
        vic_buffer_in[vic_buffer_in_len++] = i;
}

void vic_buffer_pop(void)
{
    if (vic_buffer_in_len > 0)
        vic_buffer_in[--vic_buffer_in_len] = '\0';
}

/*
  User can handle output as he wants.
*/
void vic_output_set(void (*output_func)(char))
{
    vic_output_func = output_func;
}

/*
  Processes input stream.
*/

void vic_process(char input)
{
    if (input == (char)0x08) { /* backspace */
        vic_buffer_pop();
    } else if (input == '\n') { /* new line */
        vic_exec(vic_buffer_in);
        vic_buffer_clear();
    } else {
        vic_buffer_append(input);
    }
}

#endif

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
