#ifndef _VIC_SERIAL
#define _VIC_SERIAL

#include "vic.h"

#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>


uint8_t vic_buffer_len = 0;
char vic_buffer[VIC_BUFFER_SIZE + 1] = {'\0'};


void vic_buffer_clear(void)
{
    memset(vic_buffer, '\0', VIC_BUFFER_SIZE);
    vic_buffer_len = 0;
}

void vic_buffer_append(char i)
{
    if (vic_buffer_len < VIC_BUFFER_SIZE)
        vic_buffer[vic_buffer_len++] = i;
}

void vic_buffer_pop(void)
{
    if (vic_buffer_len > 0)
        vic_buffer[--vic_buffer_len] = '\0';
}


/*
  Processes input stream.
*/

void vic_process(char input)
{
    if (input == (char)0x08) { /* backspace */
        vic_buffer_pop();
    } else if (input == '\n') { /* new line */
        vic_exec(vic_buffer);
        vic_buffer_clear();
    } else {
        vic_buffer_append(input);
    }
}

#endif

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
