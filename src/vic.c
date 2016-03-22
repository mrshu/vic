#include "vic.h"

/* VIC_ERR_NO */
const char _err_msg_0[] PROGMEM = "";

/* VIC_ERR_INSUFFICIENT_SPACE */
const char _err_msg_1[] PROGMEM = \
    "ERROR: No memory for new variable or function\n";

/* VIC_ERR_INVALID_NAME */
const char _err_msg_2[] PROGMEM = \
    "ERROR: Invalid name\n";

/* VIC_ERR_INVALID_ARGS */
const char _err_msg_3[] PROGMEM = \
    "ERROR: Arguments are of invalid type or there is wrong count of them\n";

const char * const vic_err_msg[] PROGMEM = {
    _err_msg_0,
    _err_msg_1,
    _err_msg_2,
    _err_msg_3
};

void vic_init(void (*output_func)(char))
{
    vic_output_set(output_func);
    vic_println(VIC_INIT_MESS);
    vic_print(VIC_PS1);
}

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
