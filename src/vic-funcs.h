#ifndef _VIC_FUNCS_H
#define _VIC_FUNCS_H

#define VIC_FUNC_NAME_LEN 6

struct vic_func_t {
    char name[VIC_FUNC_NAME_LEN + 1];
    void (*p_func)(void);
};

void vic_prepare_name(const char *raw_name,
                      char name[VIC_FUNC_NAME_LEN+1]);

#endif
