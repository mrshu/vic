#ifndef _VIC_VAR
#define _VIC_VAR

#include "vic.h"

#include <stdlib.h>
#include <stdint.h>

#define VIC_VAR_NONE 255

struct vic_vars{
	char* name;
	char* val;
} *vic_vars;

static uint8_t vic_varcount= 0;

void vic_var_set_new(char* name, char* val)
{
	if (vic_varcount == 0){
		vic_vars = (struct vic_vars*)
			malloc( 
				++vic_varcount * sizeof(struct vic_vars)
			);
	} else {
		vic_vars = (struct vic_vars*)
			realloc( 
				vic_vars,
				++vic_varcount * sizeof(struct vic_vars)
			);
	}

//	printf("task: %s\n", name);

	vic_vars[vic_varcount - 1].name = strdup(name);
	vic_vars[vic_varcount - 1].val = strdup(val);



}

uint8_t vic_var_get_id (char* name)
{
	int i;
	for (i = 0; i < vic_varcount; i++) {
		if (strcmp(name, vic_vars[i].name) == 0) {
			return i;
		}
	}
	return VIC_VAR_NONE;
}


void vic_var_set(char* name, char* val)
{
	
	uint8_t id = vic_var_get_id(name);
	if (id == VIC_VAR_NONE){
		vic_var_set_new(name, val);
	} else {
		free(vic_vars[id].val);
		vic_vars[id].val = strdup(val);
	}
	
}

char* vic_var_get(char* name)
{
	int i;
	for (i = 0; i < vic_varcount; i++) {
		if (strcmp(name, vic_vars[i].name) == 0) {
			return vic_vars[i].val;
		}
	}

	return 0;

}


#endif

