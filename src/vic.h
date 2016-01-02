#ifndef _VIC_H
#define _VIC_H

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>

#define vic_args(format, ...) (sscanf(vic_args_s, (format), __VA_ARGS__))
#define VIC_XSTR(s) VIC_STR(s)
#define VIC_STR(s) #s

#define VIC_PS1 "+> "
#define VIC_BUFFER_SIZE 128
#define VIC_FUNCS_COUNT 64
#define VIC_FUNC_NAME_LEN 6
#define VIC_VARS_COUNT 64
#define VIC_VAR_NAME_LEN 6
#define VIC_VAR_VAL_LEN 10

#define VIC_ERR_NO 0
#define VIC_ERR_INSUFFICIENT_SPACE 1
#define VIC_ERR_INVALID_NAME 2
#define VIC_ERR_INVALID_ARGS 3

/* vic-serial.c */
extern char vic_buffer[VIC_BUFFER_SIZE + 1];
extern uint8_t vic_buffer_len;

#define vic_print_err(id) vic_print(vic_err_msg[id])
#define vic_println(s) do { vic_print(s); vic_out('\n'); } while(0)

void vic_out(char c);
void vic_print(char *s);

void vic_buffer_append(char i);
void vic_process(char input);
void vic_output_set(void (*output_func)(char));

/* vic-funcs.c */
int8_t vic_fn_add(const char *raw_name, void (*p_func)(void));
int8_t vic_fn_call(const char *raw_name);
int8_t vic_fn_rm(const char *raw_name);
void vic_funcs_clear(void);

/* vic-var.c */
int8_t vic_var_set(const char *raw_name, char *value);
int8_t vic_var_get(const char *raw_name, char **value_out);

/* vic-exec.c */
extern char *vic_args_s;

int8_t vic_exec(char *line);

/* vic.c */
extern char *vic_err_msg[];

void vic_init();

#endif

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
