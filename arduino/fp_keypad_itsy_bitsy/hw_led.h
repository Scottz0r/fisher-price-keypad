#ifndef _SCOTTZ0R_HW_LED_INCLUDE_GUARD
#define _SCOTTZ0R_HW_LED_INCLUDE_GUARD

#include <Arduino.h>

#include "hw_led.h"
#include "hw_cfg.h"

namespace scottz0r
{
    using color_t = unsigned char;

    struct RGB
    {
        color_t r;
        color_t g;
        color_t b;
    };

    void init_led();

    void write_led(const RGB& rgb);
}

#endif //_SCOTTZ0R_HW_LED_INCLUDE_GUARD
