#ifndef _VIC_VAR
#define _VIC_VAR

#include "vic.h"
#include "vic-var.h"

struct vic_var_t vic_vars[VIC_VARS_COUNT];
uint8_t vic_vars_len = 0;

void vic_vars_clear(void)
{
    memset(vic_vars, 0, sizeof(struct vic_var_t) * VIC_VARS_COUNT);
    vic_vars_len = 0;
}

int8_t vic_var_set(const char *raw_name, const char *value)
{
    char name[VIC_VAR_NAME_LEN+1] = {'\0'};

    strncpy(name, raw_name, VIC_VAR_NAME_LEN);

    uint8_t i;
    /* find variable in vic_vars array */
    for (i = 0; i < vic_vars_len; i++) {
        /* set value to variable when found */
        if (strcmp(name, vic_vars[i].name) == 0) {
            strncpy(vic_vars[i].value, value, VIC_VAR_VAL_LEN);
            vic_var_set_bind_val(&vic_vars[i]);
            return VIC_ERR_NO;
        }
    }
    /* if variable doesn't exist, make new one */

    /* check if there is enough space */
    if (vic_vars_len == VIC_VARS_COUNT) {
        return VIC_ERR_INSUFFICIENT_SPACE;
    }

    struct vic_var_t new_var;
    strcpy(new_var.name, name);
    strncpy(new_var.value, value, VIC_VAR_VAL_LEN);
    new_var.value[VIC_VAR_VAL_LEN] = '\0';
    new_var.bind_val = NULL;
    new_var.type = VIC_VAR_NONE;

    vic_vars[vic_vars_len] = new_var;

    vic_vars_len++;
    return VIC_ERR_NO;
}

int8_t vic_var_get(const char *raw_name, char **value_out)
{
    char name[VIC_VAR_NAME_LEN+1] = {'\0'};
    strncpy(name, raw_name, VIC_VAR_NAME_LEN);

    uint8_t i;
    for (i = 0; i < vic_vars_len; i++) {
        if (strcmp(name, vic_vars[i].name) == 0) {
            /* found variable with that name */
            *value_out = (char *)vic_vars[i].value;
            return VIC_ERR_NO;
        }
    }
    /* no variable with that name */
    return VIC_ERR_INVALID_NAME;
}

int8_t vic_var_bind(const char *raw_name, void *bind_val, const uint8_t type)
{
    char name[VIC_VAR_NAME_LEN+1] = {'\0'};
    strncpy(name, raw_name, VIC_VAR_NAME_LEN);

    uint8_t i;
    for (i = 0; i < vic_vars_len; i++) {
        if (strcmp(name, vic_vars[i].name) == 0) {
            /* found variable with that name */
            vic_vars[i].bind_val = bind_val;
            vic_vars[i].type = type;
            vic_var_set_bind_val(&vic_vars[i]);
            return VIC_ERR_NO;
        }
    }
    /* no variable with that name */
    return VIC_ERR_INVALID_NAME;
}

void vic_var_set_bind_val(struct vic_var_t *vic_var)
{
    if (vic_var->bind_val == NULL) {
        return;
    }
    switch (vic_var->type) {
        case VIC_VAR_INT8 :
            *((int8_t *)vic_var->bind_val) = (int8_t)atoi(vic_var->value);
            return;
        case VIC_VAR_UINT8 :
            *((uint8_t *)vic_var->bind_val) = (uint8_t)atoi(vic_var->value);
            return;
        case VIC_VAR_INT16 :
            *((int16_t *)vic_var->bind_val) = (int16_t)atoi(vic_var->value);
            return;
        case VIC_VAR_UINT16 :
            *((uint16_t *)vic_var->bind_val) = (uint16_t)atol(vic_var->value);
            return;
        /*
        case VIC_VAR_INT32 :
            *((int32_t *)vic_var->bind_val) = (int32_t)atol(vic_var->value);
            return;
        case VIC_VAR_UINT32 :
            *((uint32_t *)vic_var->bind_val) = (uint32_t)atol(vic_var->value);
            return;
        */
        case VIC_VAR_FLOAT :
            *((float *)vic_var->bind_val) = (float)atof(vic_var->value);
            return;
    }
}

#endif

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
