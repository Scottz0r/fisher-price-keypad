#include "color_mapper.h"

#include <Arduino.h>
#include <avr/pgmspace.h>

#include "hw_cfg.h"
#include "prj_generic_types.h"
#include "color_tables.h"
#include "look_up_table.h"
#include "globals.h"

namespace scottz0r {

    static const LookUpTable red_table(colors::red_lut, color_count(colors::red_lut));

    static const LookUpTable green_table(colors::green_lut, color_count(colors::green_lut));

    static const LookUpTable blue_table(colors::blue_lut, color_count(colors::blue_lut));

    static const LookUpTable pink_table(colors::pink_lut, color_count(colors::pink_lut));

    static const LookUpTable purple_table(colors::purple_lut, color_count(colors::purple_lut));

    static const LookUpTable orange_table(colors::orange_lut, color_count(colors::orange_lut));

    const LookUpTable* map_key_to_color(char key_char)
    {
        switch(key_char)
        {
        case 'B':
        case 'E':
        case 'M':
        case 'O':
        case 'X':
            return &red_table;
        case 'A':
        case 'G':
        case 'I':
        case 'L':
        case 'T':
        case 'W':
            return &green_table;
        case 'D':
        case 'J':
        case 'R':
        case 'U':
        case 'V':
        case 'Y':
            return &blue_table;
        case 'F':
        case 'K':
            return &pink_table;
        case 'C':
        case 'N':
        case 'P':
        case 'S':
            return &purple_table;
        case 'H':
        case 'Q':
        case 'Z':
            return &orange_table;
        // TODO - there are ' ' and '\n', but IDK what to map them to.
        default:
            // Default to nothing.
            return nullptr;
        }

        return nullptr;
    }

}
