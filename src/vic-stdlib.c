#ifndef _VIC_STDLIB
#define _VIC_STDLIB

#include "vic.h"
#include "stdlib.h"

void vic_set(void)
{
    char var_name[VIC_VAR_NAME_LEN+1] = {'\0'};
    char var_val[VIC_VAR_VAL_LEN+1] = {'\0'};

    char *args_format = "%"VIC_XSTR(VIC_VAR_NAME_LEN)"s";
    if (vic_args(args_format, var_name) != 1) {
        vic_print_err(VIC_ERR_INVALID_ARGS);
        return;
    }
    args_format = "%*s %"VIC_XSTR(VIC_VAR_VAL_LEN)"s";
    if (vic_args(args_format, var_val) != 1) {
        vic_print_err(VIC_ERR_INVALID_ARGS);
        return;
    }

    int8_t error = vic_var_set(var_name, var_val);

    vic_print_err(error);
}

void vic_get(void)
{
    char var_name[VIC_VAR_NAME_LEN+1] = {'\0'};
    char *args_format = "%"VIC_XSTR(VIC_VAR_NAME_LEN)"s";

    if (vic_args(args_format, var_name) != 1) {
        vic_print_err(VIC_ERR_INVALID_ARGS);
        return;
    }

    char *value = NULL;
    int8_t error = vic_var_get(var_name, &value);

    vic_print_err(error);
    if (value != NULL) {
        vic_println(value);
    }
}

#endif

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
