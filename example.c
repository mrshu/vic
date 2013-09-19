#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

#define SHELL 0
#define DEBUG 0
#include <vic.h>

void test()
{
        int t;
        vic_args("%d", &t);
        printf("test, args: %s, t = %d\n", vic_buff, t);
        vic_return("%d", t+1);
}

void whl()
{
        char inp[65];
        vic_args("%s", &inp);
}

void ls()
{
        vic_print("listing");
}

int simple_changable_value = 1;
void p()
{
        printf("simple_changable_value = %d\n", simple_changable_value);
}

void rm()
{
        char i[20];
        vic_args("%s", &i);
        printf("Removing %s\n", i);
        vic_exec("ls;");

}

void milis()
{
        vic_func();

        vic_return("%d", rand());
}

int main(void)
{

        //vic_fn_add("A", &test);
        vic_init();

        vic_fn_add("l", &ls);
        vic_fn_add("rm", &rm);
        vic_fn_add("test", &test);
        vic_fn_add("m", &milis);
        vic_fn_add("prs", &p);

        vic_alias_add("time", "rpc;m;shell;");

        vic_exec("l;");

        vic_var_set_bind("s", "10", &simple_changable_value);

        int argc = 0;
        char **argv = vic__args("2 'A B' \"C D E\"", &argc);

        int j = 0;
        for (j = 0; j < argc; j++) {
                printf("%s\n", argv[j]);
        }

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
