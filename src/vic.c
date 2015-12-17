#include "vic.h"

void vic_prepare_name(const char *raw_name, char *name, int len)
{
    memset(name, '\0', len + 1);
    if (strlen(raw_name) > len) {
        memcpy(name, raw_name, len);
    } else {
        strcpy(name, raw_name);
    }
}

void vic_init()
{

}

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
