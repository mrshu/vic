#ifndef _VIC_FUNCS
#define _VIC_FUNCS

#include "vic.h"
#include "vic-funcs.h"

struct vic_func_t vic_funcs[VIC_FUNCS_COUNT];
int vic_funcs_len = 0;

void vic_funcs_clear(void)
{
    memset(vic_funcs, 0, sizeof(struct vic_func_t) * vic_funcs_len);
    vic_funcs_len = 0;
}

int vic_fn_add(const char *raw_name, void (*p_func)(void))
{
    /* there is no space for next function */
    if (vic_funcs_len == VIC_FUNCS_COUNT) {
        return VIC_ERR_FUNC_INSUFFICIENT_SPACE;
    }

    char name[VIC_FUNC_NAME_LEN+1];
    vic_prepare_name(raw_name, name, VIC_FUNC_NAME_LEN);

    int i;
    /* traverse vic_funcs to find out if there already is this function */
    for (i = 0; i < vic_funcs_len; i++) {
        /* if yes, overwrite it */
        if (strcmp(name, vic_funcs[i].name) == 0) {
            vic_funcs[i].p_func = p_func;
            return VIC_ERR_NO;
        }
    }
    /* if not, make new one */
    struct vic_func_t new_func;
    new_func.p_func = p_func;
    strcpy(new_func.name, name);
    vic_funcs[vic_funcs_len] = new_func;

    vic_funcs_len++;
    return VIC_ERR_NO;
}

int vic_fn_call(const char *raw_name)
{
    char name[VIC_FUNC_NAME_LEN + 1];
    vic_prepare_name(raw_name, name, VIC_FUNC_NAME_LEN);
    int i;
    for (i = 0; i < vic_funcs_len; i++) {
        if (strcmp(name, vic_funcs[i].name) == 0) {
            /* found function to call */
            (*(vic_funcs[i].p_func))();
            return VIC_ERR_NO;
        }
    }
    return VIC_ERR_FUNC_WRONG_NAME;
}

int vic_fn_rm(const char *raw_name)
{
    char name[VIC_FUNC_NAME_LEN + 1];
    vic_prepare_name(raw_name, name, VIC_FUNC_NAME_LEN);
    int i;
    for (i = 0; i < vic_funcs_len; i++) {
        if (strcmp(name, vic_funcs[i].name) == 0) {
            /* found function to remove */
            int j;
            for (j = i; j < vic_funcs_len - 1; j++) {
                vic_funcs[j].p_func = vic_funcs[j+1].p_func;
                strcpy(vic_funcs[j].name, vic_funcs[j+1].name);
            }
            vic_funcs_len--;
            return VIC_ERR_NO;
        }
    }
    return VIC_ERR_FUNC_WRONG_NAME;
}

#endif

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
