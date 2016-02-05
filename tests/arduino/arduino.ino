#include "vic.h"

/***************************************
MAKE SURE YOU HAVE SET '\n' LINE ENDINGS
***************************************/

uint8_t led_state;

void set_led(void)
{
    char status[5];
    if (vic_args("%3s", &status) == 1) {
        if (strcmp(status, "on") == 0) {
            led_state = 1;
        } else if (strcmp(status, "off") == 0) {
            led_state = 0;
        }
    }
}

void led_on(void)
{
    led_state = 1;
}

void led_off(void)
{
    led_state = 0;
}

void serial_print(char c)
{
    Serial.print(c);
}


void setup()
{
    Serial.begin(115200);
    pinMode(13, OUTPUT);

    vic_output_set(serial_print);

    vic_fn_add("on", led_on);
    vic_fn_add("off", led_off);
    vic_fn_add("led", set_led);

    vic_var_set("state", "0");
    vic_var_bind("state", &led_state, VIC_VAR_UINT8);

    Serial.println(F("Try to use these commands: (type them and hit enter)"));
    Serial.println(F("\ton\n\toff"));
    Serial.println(F("\tled on\n\tled off"));
    Serial.println(F("\tset state 1\n\tset state 0"));
    Serial.println(F("and see LED attached to pin 13"));

    Serial.println(F(VIC_PS1));
}

void loop()
{
    if (Serial.available() > 0) {
        char c = Serial.read();
        vic_process(c);
        if (c == '\n') {
            Serial.println(F(VIC_PS1));
        }
    }

    digitalWrite(13, led_state);
}

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
