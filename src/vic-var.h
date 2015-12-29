#ifndef _VIC_VAR_H
#define _VIC_VAR_H

#include "vic.h"

struct vic_var_t {
    char name[VIC_VAR_NAME_LEN + 1];
    char *p_value;
};

#endif

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
