#include "color_manager.h"

#include <Arduino.h>
#include <avr/pgmspace.h>

#include "hw_cfg.h"
#include "prj_generic_types.h"
#include "color_tables.h"
#include "look_up_table.h"
#include "globals.h"

namespace scottz0r { namespace colorman {

    static constexpr time_type animation_time_ms = 1000;

    enum class COLOR : char
    {
        NONE,
        PINK
    };

    LookUpTable pink_table(colors::pink_lut, color_count(colors::pink_lut));
    // TODO - more tables.

    // TODO - actually map
    static const COLOR color_map[] PROGMEM = 
    {
        COLOR::PINK, // 'A',
        COLOR::PINK, // 'B',
        COLOR::PINK, // 'C',
        COLOR::PINK, // 'D',
        COLOR::PINK, // 'E',
        COLOR::PINK, // 'F',
        COLOR::PINK, // 'G',
        COLOR::PINK, // 'H',
        COLOR::PINK, // 'I',
        COLOR::PINK, // 'J',
        COLOR::PINK, // 'K',
        COLOR::PINK, // 'L',
        COLOR::PINK, // 'M',
        COLOR::PINK, // 'N',
        COLOR::PINK, // 'O',
        COLOR::PINK, // 'P',
        COLOR::PINK, // 'Q',
        COLOR::PINK, // 'R',
        COLOR::PINK, // 'S',
        COLOR::PINK, // 'T',
        COLOR::PINK, // 'U',
        COLOR::NONE, // ' ',
        COLOR::PINK, // 'V',
        COLOR::PINK, // 'W',
        COLOR::PINK, // 'X',
        COLOR::PINK, // 'Y',
        COLOR::PINK, // 'Z',
        COLOR::NONE, // '\n'
    };

    static constexpr size_type color_map_size = scottz0r_array_size(color_map);

    void begin()
    {
        pinMode(RED_LED, OUTPUT);
        pinMode(GREEN_LED, OUTPUT);
        pinMode(BLUE_LED, OUTPUT);

        write_led(RGB{});
    }

    void play(int key_code)
    {
        if (key_code < color_map_size)
        {
            COLOR c = (COLOR)pgm_read_byte_near(color_map + key_code);

            switch(c)
            {
            case COLOR::PINK:
                led_manager.set(pink_table, animation_time_ms);
                break;
            default:
                // Do nothing
                break;
            }
        }
    }

}}
