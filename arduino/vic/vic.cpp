

#if defined(ARDUINO) && ARDUINO >= 100
#include <avr/pgmspace.h>
#include "Arduino.h"
#else
    #if defined(ARDUINO)
        #include <avr/pgmspace.h>
        #include "WProgram.h"
    #else
        #if defined(HIGH)
            #define ARDUINO 1
            #include <avr/pgmspace.h>
            #include "WProgram.h"
        #endif
    #endif
#endif

#include "src/vic.c"
#include "src/vic-funcs.c"
#include "src/vic-serial.c"
#include "src/vic-tasks.c"
#include "src/vic-var.c"

