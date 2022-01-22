#include "keypad.h"

#include <avr/pgmspace.h>
#include <Arduino.h>
#include "hw_cfg.h"

namespace scottz0r {
    
    static constexpr int row_pins_count = scottz0r_array_size(keypad_row_pins);
    static constexpr int col_pins_count = scottz0r_array_size(keypad_col_pins);

    // Maps key number to ASCII character. The index must match the key index on the keypad,
    // which is found by (r * col_pins_count) + c
    static const char keymap[] PROGMEM = 
    {
        'A',
        'B',
        'C',
        'D',
        'E',
        'F',
        'G',
        'H',
        'I',
        'J',
        'K',
        'L',
        'M',
        'N',
        'O',
        'P',
        'Q',
        'R',
        'S',
        'T',
        'U',
        ' ',
        'V',
        'W',
        'X',
        'Y',
        'Z',
        '\n'
    };
    static constexpr int keymap_size = scottz0r_array_size(keymap);

    Keypad::Keypad()
    {

    }

    void Keypad::begin()
    {
        // Rows set as output, set high.
        for (int i = 0; i < row_pins_count; ++i)
        {
            pinMode(keypad_row_pins[i], OUTPUT);
            digitalWrite(keypad_row_pins[i], HIGH);  
        }

        // Columns input with pullup (Low = on)
        for (int i = 0; i < col_pins_count; ++i)
        {
            pinMode(keypad_col_pins[i], INPUT_PULLUP);
        }

        // Set killswitch as input pulled up. If connected to ground, it will disable the keyboard.
        pinMode(killswitch_pin, INPUT_PULLUP);
    }

    char Keypad::process()
    {
        time_type now = millis();
        time_type elapsed = now - m_last_scan;

        if (elapsed < POLL_RATE)
        {
            return no_key;
        }

        char result = no_key;
        int key = scan_pad();

        if (key >= 0 && key < keymap_size)
        {
            result = handle_keydown(key);
        }
        else
        {
            if (m_prev_key_code != NO_BUTTON)
            {
                result = key_release;
            }

            // No key pressed. Clear last key.
            m_prev_key_code = NO_BUTTON;            
        }

        m_last_scan = now;

        return result;
    }

    // Scan the keypad for a pressed button. This will return after finding the first button pressed.
    // This assumes the columns are inputs with pullups and the rows are outputs.
    int Keypad::scan_pad()
    {
        int result = NO_BUTTON;

        for (int r = 0; r < row_pins_count; ++r)
        {
            // Write row low.
            int row_pin = keypad_row_pins[r];
            digitalWrite(row_pin, LOW);

            // Read columns to see if any are pulled low.
            for (int c = 0; c < col_pins_count; ++c)
            {
                int col_pin = keypad_col_pins[c];
                int pin_value = digitalRead(col_pin);

                // These pins are pulled up, so low means they are connected to ground via the row pin.
                if (!pin_value)
                {
                    // Set the button number, counting by rows then columns. Stop the column looping. Cannot use a
                    // return here because the pin still needs to be reset to the default state of HIGH.
                    result = (r * col_pins_count) + c;
                    break;
                }
            }

            // Write row back high after polling columns.
            digitalWrite(row_pin, HIGH);

            // Stop row loops if a button found.
            if (result != NO_BUTTON)
            {
                break;
            }
        }

        return result;
    }

    // Handle a key being pressed, sending the keystroke to the deviced plugged in via USB.
    char Keypad::handle_keydown(int key_code)
    {
        // Killswitch low = keyboard disabled.
        int is_killed = digitalRead(killswitch_pin);
        if (!is_killed)
        {
            return no_key;
        }

        // Do nothing if the same key is pressed.
        if (m_prev_key_code == key_code)
        {
            return no_key;
        }

        // Get ASCII character representation.
        char c = (char)pgm_read_byte_near(keymap + key_code);

        // Save last key press to avoid double pressing. This also helps with debounce, too.
        m_prev_key_code = key_code;

        return c;
    }
}
