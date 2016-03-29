#ifndef _VIC_FUNCS
#define _VIC_FUNCS

#include "vic.h"
#include "vic-funcs.h"
#include "vic-stdlib.h"

struct vic_func_t vic_funcs[VIC_ALL_FUNCS_COUNT] = {
    { "set", vic_set },
    { "get", vic_get },
    { "ls", vic_list },
    { "lsv", vic_list_vars }
};
uint8_t vic_funcs_len = VIC_INTERN_FUNCS_COUNT;

void vic_funcs_clear(void)
{
    /* delete only user-defined funcs */
    void *start = vic_funcs + VIC_INTERN_FUNCS_COUNT;
    memset(start, 0, sizeof(struct vic_func_t) * VIC_FUNCS_COUNT);
    vic_funcs_len = VIC_INTERN_FUNCS_COUNT;
}

uint8_t vic_fn_add(const char *raw_name, void (*p_func)(void))
{
    char name[VIC_FUNC_NAME_LEN+1] = {'\0'};
    strncpy(name, raw_name, VIC_FUNC_NAME_LEN);

    uint8_t i;
    /* traverse vic_funcs to find out if there already is this function */
    for (i = 0; i < vic_funcs_len; i++) {
        /* if yes, overwrite it */
        if (strcmp(name, vic_funcs[i].name) == 0) {
            vic_funcs[i].p_func = p_func;
            return VIC_ERR_NO;
        }
    }
    /* if not, make new one */

    /* there is no space for next function */
    if (vic_funcs_len == VIC_ALL_FUNCS_COUNT) {
        return VIC_ERR_INSUFFICIENT_SPACE;
    }

    struct vic_func_t new_func;
    new_func.p_func = p_func;
    strcpy(new_func.name, name);
    vic_funcs[vic_funcs_len] = new_func;

    vic_funcs_len++;
    return VIC_ERR_NO;
}

uint8_t vic_fn_call(const char *raw_name)
{
    char name[VIC_FUNC_NAME_LEN + 1] = {'\0'};
    strncpy(name, raw_name, VIC_FUNC_NAME_LEN);

    uint8_t i;
    for (i = 0; i < vic_funcs_len; i++) {
        if (strcmp(name, vic_funcs[i].name) == 0) {
            /* found function to call */
            (*(vic_funcs[i].p_func))();
            return VIC_ERR_NO;
        }
    }
    return VIC_ERR_INVALID_NAME;
}

uint8_t vic_fn_rm(const char *raw_name)
{
    char name[VIC_FUNC_NAME_LEN + 1] = {'\0'};
    strncpy(name, raw_name, VIC_FUNC_NAME_LEN);

    uint8_t i;
    for (i = 0; i < vic_funcs_len; i++) {
        if (strcmp(name, vic_funcs[i].name) == 0) {
            /* found function to remove */
            if (i < VIC_INTERN_FUNCS_COUNT) {
                /* intern func - leave blank space */
                vic_funcs[i].p_func = NULL;
                memset(vic_funcs[i].name, 0, VIC_FUNC_NAME_LEN);
            } else {
                /* user-defined func - shift all after this by one index */
                uint8_t j;
                for (j = i; j < vic_funcs_len - 1; j++) {
                    vic_funcs[j].p_func = vic_funcs[j+1].p_func;
                    strcpy(vic_funcs[j].name, vic_funcs[j+1].name);
                }
                vic_funcs_len--;
            }
            return VIC_ERR_NO;
        }
    }
    return VIC_ERR_INVALID_NAME;
}

#endif

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
