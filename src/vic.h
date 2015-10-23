#ifndef _VIC_H
#define _VIC_H 1

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>

#define vic_sys_print(x) printf("%s", x)
#define vic_sys_out(x) printf("%c", x)
#define vic_sys_println(x) printf("%s\n", x)

#define VIC_PS1 "+> "
#define VIC_BUFFER_SIZE 128

/* vic-serial.c */
extern char vic_buffer[VIC_BUFFER_SIZE];
extern int vic_buffer_len;

void vic_buffer_append(char i);
void vic_process(char input);

/* vic.c */
void vic_init();

#endif
