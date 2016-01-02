#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define SHELL 0
#define DEBUG 0
#include <vic.h>

int main(void)
{
    vic_init();
    vic_output_set((void (*)(char))putchar);
    while (1) {
        vic_print(VIC_PS1);

        char c;
        while ((c = getchar()) != '\n') {
            vic_process(c);
        }
        vic_process('\n');
    }

    return 0;
}

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
