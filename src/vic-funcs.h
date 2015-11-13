#ifndef _VIC_FUNCS_H
#define _VIC_FUNCS_H

#define VIC_FUNC_NAME_LEN 6

typedef struct vic_func {
    char name[VIC_FUNC_NAME_LEN + 1];
    void (*p_func)();
} VIC_FUNC;

#endif
