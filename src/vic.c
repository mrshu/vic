#include "vic.h"

uint8_t vic_config = 0;

void vic_func_rpc()
{
	vic_config |= VIC_RPC;
}

void vic_func_shell()
{
	vic_config ^= VIC_RPC;
}



#ifdef ARDUINO

// from http://forum.pololu.com/viewtopic.php?f=10&t=989#p4218
void vic_func_free()
{
	vic_func();

	extern int __bss_end;
	int ret;
	vic_return("%d",  ((int)&ret) - ((int)&__bss_end));

}

void vic_func_millis()
{
	vic_func();
	vic_return("%ld", millis());
}


void vic_func_pinmode()
{
	uint8_t pin, mode;
	vic_args("%d %d", &pin, &mode);
	pinMode(pin, mode);
}

void vic_func_dr()
{
	uint8_t pin;
	vic_args("%d", &pin);
	vic_return("%d", digitalRead(pin));

}

void vic_func_dw()
{
	int pin, val;
	vic_args("%d %d", &pin, &val);
    digitalWrite(pin, val);
}

void vic_func_ar()
{
	uint8_t pin;
	vic_args("%d", &pin);
	vic_return("%d", analogRead(pin));
}

void vic_func_aw()
{
	uint8_t pin;
	int val;
	vic_args("%d %d", &pin, &val);
        analogWrite(pin, val);
}

#endif
void vic_func_start()
{
	char *tmp;
	tmp = NULL;
	tmp = (char *) malloc(31 * sizeof(char));
	int time;
	vic_args("%30s %d", tmp, &time);

	vic_task_start(tmp, time);
}

void vic_func_stop()
{
	uint8_t id;
	vic_args("%d", &id);

	vic_task_stop(id);
}


void vic_func_set()
{
	char* name;
	name = (char *) malloc(31 * sizeof(char));
	char* val;
	val = (char *) malloc(31 * sizeof(char));

	vic_args("%30s %30s", name, val);

	vic_var_set(name, val);
	free(name);
	free(val);

}

void vic_func_p()
{
	char* name;
	name = (char *) malloc(31 * sizeof(char));
	vic_args("%30s", name);

	vic_return("%s", vic_var_get(name));
}

void vic_run(void)
{
	if (vic_available()){
		vic_process(vic_in());
	}

	vic_tasks_run();

}
#ifdef ARDUINO
void vic_init(unsigned long baud)
{
	vic_inout_init(baud);
#else
void vic_init()
{
#endif
	vic_fn_add("ls", &vic_func_ls);
	vic_fn_add("rpc", &vic_func_rpc);
	vic_fn_add("shell", &vic_func_shell);
        vic_fn_add("echo", &vic_func_echo);

#ifdef SHELL
	vic_println("beign");
	vic_print(VIC_PS1);
#endif


#ifdef ARDUINO

	vic_fn_add("free", &vic_func_free);
	vic_fn_add("millis", &vic_func_millis);


	vic_fn_add("pm", &vic_func_pinmode);
	vic_fn_add("dr", &vic_func_dr);
	vic_fn_add("dw", &vic_func_dw);
	vic_fn_add("ar", &vic_func_ar);
	vic_fn_add("aw", &vic_func_aw);
#endif
	vic_fn_add("start", &vic_func_start);
	vic_fn_add("stop", &vic_func_stop);
	vic_fn_add("ps", &vic_func_ps);

/*
	vic_fn_add("=", &vic_func_set);
	vic_fn_add("p", &vic_func_p);

*/
}
