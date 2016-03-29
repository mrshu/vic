#ifndef _VIC_VAR_H
#define _VIC_VAR_H

#include "vic.h"
#include <stdint.h>

struct vic_var_t {
    char name[VIC_VAR_NAME_LEN + 1];
    char value[VIC_VAR_VAL_LEN + 1];
    void *bind_val;
    uint8_t type;
};

extern struct vic_var_t vic_vars[VIC_VARS_COUNT];
extern uint8_t vic_vars_len;

/* sets value to bind_val */
void vic_var_update_bind_val(struct vic_var_t *vic_var);
/* sets bind_val to value */
void vic_var_update_value(struct vic_var_t *vic_var);

#endif

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
