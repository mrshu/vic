#ifndef _VIC_SERIAL
#define _VIC_SERIAL

#include "vic.h"

#include <stdlib.h>
#include <stdint.h>
#include <ctype.h>


static int vic_buffer_len = 0;
char vic_buffer[VIC_BUFFER_SIZE];


void vic_buffer_append(char i)
{
        vic_buffer[vic_buffer_len++] = i;
}


/*
  Processes input stream.
*/

void vic_process(char input)
{
}

#endif
