#ifndef _VIC_H
#define _VIC_H 1

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdint.h>


#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #if defined(ARDUINO)
    #include "WProgram.h"
  #endif
#endif

#if defined(ARDUINO)
#define SHELL 1

/*
void vic_print(char *x);
void vic_out(char x);
void vic_println(char x);

void vic_inout_init(unsigned long baud);
int vic_available();
char vic_in();
*/

#if !defined(VIC_ARDUINO_SERIAL)
  #define VIC_ARDUINO_SERIAL Serial
#endif

#define vic_out(x) VIC_ARDUINO_SERIAL.print(x)
#define vic_print(x) VIC_ARDUINO_SERIAL.print(x)
#define vic_println(x) VIC_ARDUINO_SERIAL.println(x)

#define vic_inout_init(x) VIC_ARDUINO_SERIAL.begin(x)
#define vic_available VIC_ARDUINO_SERIAL.available
#define vic_in VIC_ARDUINO_SERIAL.read

#else

#define vic_print(x) printf("%s", x)
#define vic_out(x) printf("%c", x)
#define vic_println(x) printf("%s\n", x)

#define vic_inout_init(baud);
#define vic_available() 1
#define vic_in getchar

#include <time.h>
#define millis() time(0)

#endif

#define VIC_MAX_CHARS 80
#define vic_args(fmt, ...) sscanf(vic_buff, fmt, __VA_ARGS__); \
char *_vifunc_; _vifunc_ = vic_func;

#define vic_func(); char *_vifunc_; _vifunc_ = vic_func;


#define vic_return(fmt, ...) \
{char *tmp; \
tmp = (char *) malloc(sizeof(char) * VIC_MAX_CHARS); \
if (vic_config & VIC_RPC) { \
sprintf(tmp, "%%%s " fmt "$", _vifunc_ , __VA_ARGS__);} else { \
sprintf(tmp, fmt, __VA_ARGS__); } \
vic_println(tmp); \
free(tmp);vic_returned = 1;}

#define STR(x) #x
#define TOSTR(x) STR(x)
#define dprint_str(str) if (DEBUG) printf(__FILE__ ":" TOSTR(__LINE__) "> " TOSTR(str) \
                    " = '%s'\n", str)

#define dprint_int(str) if (DEBUG) printf(__FILE__ ":" TOSTR(__LINE__) "> " TOSTR(str) \
                    " = %d\n", str)

#define dprint_char(str) if(DEBUG) printf(__FILE__ ":" TOSTR(__LINE__) "> " TOSTR(str) \
                    " = %c\n", str)


void vic_fn_add_mask(char* name, void(*fn)(), uint8_t mask);
#define vic_fn_add(name, fn)  vic_fn_add_mask(name, fn, 0)
int vic_fn_call(const char* name);

char* vic_alias(char *name);
void vic_alias_add(char *name, char *alias);

/* vic-serial.c */
extern char *vic_buffer;
extern char *vic_buff;
extern char *vic_func;
extern uint8_t vic_returned;

void vic_buffer_append(char i);

void vic_process(char input);
void vic_exec(char *input);


void vic_print_int(int i);
void vic_print_int_base(int i, uint8_t n);
void vic_print_hex(int i);


void vic_func_ls(void);
#ifdef ARDUINO
void vic_init(unsigned long baud);
#else
void vic_init();
#endif

void vic_run(void);

#define VIC_RPC 0x8

#define VIC_PS1 "+> "

extern uint8_t vic_config;

void vic_task_stop(uint8_t id);
void vic_task_start(char* name, unsigned int delay);
void vic_tasks_run(void);
void vic_func_ps(void);


void vic_var_set_bind(char* name, char* val, void* pval);
#define vic_var_set(name, val) vic_var_set_bind(name, val, NULL)
char* vic_var_get(char* name);
#define vic_var_set_new(name, val) vic_var_set_new_bind(name, val, NULL)
char **vic__args(const char* in, int *argc);


void vic_func_echo(void);

#endif
