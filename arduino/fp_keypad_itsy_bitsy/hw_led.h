#ifndef _SCOTTZ0R_HW_LED_INCLUDE_GUARD
#define _SCOTTZ0R_HW_LED_INCLUDE_GUARD

namespace scottz0r
{
    using color_t = unsigned char;

    struct RGB
    {
        color_t r;
        color_t g;
        color_t b;
    };

    void write_led(const RGB& rgb);
}

#endif //_SCOTTZ0R_HW_LED_INCLUDE_GUARD
