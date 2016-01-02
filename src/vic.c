#include "vic.h"

char *vic_err_msg[] = {
    /* VIC_ERR_NO */
    "",

    /* VIC_ERR_INSUFFICIENT_SPACE */
    "ERROR: No memory for new variable or function\n",

    /* VIC_ERR_INVALID_NAME */
    "ERROR: Invalid name\n",

    /* VIC_ERR_INVALID_ARGS */
    "ERROR: Arguments are of invalid type or there is wrong count of them\n"
};

void vic_init()
{

}

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
