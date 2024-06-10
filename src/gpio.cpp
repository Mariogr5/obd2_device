#include "gpio.hpp"

void setup_gpios_mode()
{
    pinMode(LED1, OUTPUT);
}

void set_gpios_high()
{
    digitalWrite(LED1, HIGH);
}
void set_gpios_low()
{
    digitalWrite(LED1, LOW);
}