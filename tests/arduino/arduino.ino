#include "vic.h"

/***************************************
MAKE SURE YOU HAVE SET '\n' LINE ENDINGS
***************************************/

void set_led(void)
{
    int status;
    if (vic_args("%d", &status) == 1) {
        digitalWrite(13, status);
    }
}

void led_on(void)
{
    digitalWrite(13, HIGH);
}

void led_off(void)
{
    digitalWrite(13, LOW);
}

void setup()
{
    Serial.begin(115200);
    pinMode(13, OUTPUT);

    vic_fn_add("on", led_on);
    vic_fn_add("off", led_off);
    vic_fn_add("set", set_led);
}

void loop()
{
    if (Serial.available() > 0) {
        vic_process((char)Serial.read());
    }
}

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
