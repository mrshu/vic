#ifndef _VIC_VAR
#define _VIC_VAR

#include "vic.h"
#include "vic-var.h"

struct vic_var_t vic_vars[VIC_VARS_COUNT];
uint8_t vic_vars_len = 0;

int8_t vic_var_set(const char *raw_name, char *value)
{
    char name[VIC_VAR_NAME_LEN+1];
    vic_prepare_name(raw_name, name, VIC_VAR_NAME_LEN);

    uint8_t i;
    /* find variable in vic_vars array */
    for (i = 0; i < vic_vars_len; i++) {
        /* set value to variable when found */
        if (strcmp(name, vic_vars[i].name) == 0) {
            vic_vars[i].p_value = value;
            return VIC_ERR_NO;
        }
    }
    /* if variable doesn't exist, make new one */

    /* check if there is enough space */
    if (vic_vars_len == VIC_VARS_COUNT) {
        return VIC_ERR_INSUFFICIENT_SPACE;
    }

    struct vic_var_t new_var;
    new_var.p_value = value;
    strcpy(new_var.name, name);
    vic_vars[vic_vars_len] = new_var;

    vic_vars_len++;
    return VIC_ERR_NO;
}

int8_t vic_var_get(const char *raw_name, char **value_out)
{
    char name[VIC_VAR_NAME_LEN+1];
    vic_prepare_name(raw_name, name, VIC_VAR_NAME_LEN);

    uint8_t i;
    for (i = 0; i < vic_vars_len; i++) {
        if (strcmp(name, vic_vars[i].name) == 0) {
            /* found variable with that name */
            *value_out = vic_vars[i].p_value;
            return VIC_ERR_NO;
        }
    }
    /* no variable with that name */
    return VIC_ERR_WRONG_NAME;
}

#endif

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
