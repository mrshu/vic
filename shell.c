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
    while(1) {
        char input[256];
        vic_print(VIC_PS1);
        gets(input);
        int i;

        for(i = 0; i < strlen(input); i++){
            vic_process(input[i]);
        }

        vic_process('\n');
    }

    return 0;
}
