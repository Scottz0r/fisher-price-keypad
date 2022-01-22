#ifndef _SCOTTZ0R_KEYPAD_H_INCLUDE_GUARD
#define _SCOTTZ0R_KEYPAD_H_INCLUDE_GUARD

#include "prj_generic_types.h"

namespace scottz0r {

    class Keypad
    {
        static constexpr time_type POLL_RATE = 30; // Rate at which the keypad will be polled.
        static constexpr int NO_BUTTON = -1; // Represents when a button is not pressed.
    public:
        Keypad();

        void begin();

        void process();
    
    private:
        int scan_pad();

        void handle_keydown(int key_code);

        int m_prev_key_code = NO_BUTTON; // The last key pressed.
        time_type m_last_scan = 0; // Time keypad last scanned.
    };
}

#endif // _SCOTTZ0R_KEYPAD_H_INCLUDE_GUARD
