#include "vic.h"

/* You can use Arduino serial monitor (in that case set line endings with line
   feed) or vic-picocom (which can be found in shell/) for talking to vic */

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

    Serial.println(F("Try to use these commands: (type them and hit enter)"));
    Serial.println(F("\ton\n\toff"));
    Serial.println(F("\tled on\n\tled off"));
    Serial.println(F("\tset state 1\n\tset state 0"));
    Serial.println(F("and see LED attached to pin 13"));
    Serial.println(F("If you want to try more:\n\tls\n\tlsv"));

    vic_init(serial_print);

    vic_fn_add("on", led_on);
    vic_fn_add("off", led_off);
    vic_fn_add("led", set_led);

    vic_var_set("state", "0");
    vic_var_bind("state", &led_state, VIC_VAR_UINT8);
}

void loop()
{
    if (Serial.available() > 0) {
        char c = Serial.read();

        /* to delete character in picocom
           '\b' (echoed by picocom itself) moves cursor on the last character
           ' ' (printed) overwrites last character to space
           '\b' (printed) moves the cursor backward again */
        if (c == '\b') Serial.print(" \b");

        vic_process(c);
    }

    digitalWrite(13, led_state);
}

/* vim: set tabstop=4:softtabstop=4:shiftwidth=4:expandtabs */
