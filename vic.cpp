#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #if defined(ARDUINO)
        #include "WProgram.h"
    #endif
#endif

#include "src/vic.c"
#include "src/vic-funcs.c"
#include "src/vic-serial.c"
#include "src/vic-exec.c"
#include "src/vic-var.c"
#include "src/vic-stdlib.c"

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
