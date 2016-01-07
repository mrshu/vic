#ifndef _VIC_FUNCS_H
#define _VIC_FUNCS_H

#include "vic.h"

#define VIC_INTERN_FUNCS_COUNT 2
#define VIC_ALL_FUNCS_COUNT (VIC_FUNCS_COUNT+VIC_INTERN_FUNCS_COUNT)

struct vic_func_t {
    char name[VIC_FUNC_NAME_LEN + 1];
    void (*p_func)(void);
};

#endif
