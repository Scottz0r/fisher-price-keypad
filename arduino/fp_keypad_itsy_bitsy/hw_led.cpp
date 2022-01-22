#include <Arduino.h>

#include "hw_led.h"
#include "hw_cfg.h"

namespace scottz0r
{
    void init_led()
    {
        pinMode(RED_LED, OUTPUT);
        pinMode(GREEN_LED, OUTPUT);
        pinMode(BLUE_LED, OUTPUT);

        write_led(RGB{});
    }

    void write_led(const RGB& rgb)
    {
        // Flip the color because this is common annode and using current sinks.
        analogWrite(RED_LED, 255 - rgb.r);
        analogWrite(GREEN_LED, 255 - rgb.g);
        analogWrite(BLUE_LED, 255 - rgb.b);
    }
}
