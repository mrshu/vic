#ifndef _VIC_FUNCS
#define _VIC_FUNCS

#include "vic.h"
#include "vic-funcs.h"

VIC_FUNC vic_funcs[VIC_FUNCS_COUNT];
int vic_funcs_len = 0;

void vic_funcs_clear(void)
{
    memset(vic_funcs, 0, sizeof(VIC_FUNC) * vic_funcs_len);
    vic_funcs_len = 0;
}

int vic_fn_add(const char *raw_name, void (*p_func)())
{
    /* there is no space for next function */
    if (vic_funcs_len == VIC_FUNCS_COUNT) {
        return VIC_FUNC_INSUFFICIENT_SPACE;
    }

    char name[VIC_FUNC_NAME_LEN + 1] = {'\0'};
    /* make sure name length isn't larger than it should */
    if (strlen(raw_name) > VIC_FUNC_NAME_LEN) {
        memcpy(name, raw_name, VIC_FUNC_NAME_LEN);
    } else {
        strcpy(name, raw_name);
    }
    /* add function */
    VIC_FUNC new_func;
    strcpy(new_func.name, name);
    new_func.p_func = p_func;
    vic_funcs[vic_funcs_len] = new_func;

    vic_funcs_len++;
    return VIC_NO_ERR;
}

#endif

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
