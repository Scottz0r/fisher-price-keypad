// Author: Scott Clewell
// January 2022
// Program to turn a Fisher Price "Smart Stages" tablet into a HID Keyboard device.
// Requires a custom PBC (which I have conveniently designed) to replace the PCB that comes with the Keypad.
#include <Arduino.h>
#include <Keyboard.h>

#include "prj_generic_types.h"
#include "color_mapper.h"
#include "globals.h"

using namespace scottz0r;

static constexpr time_type animation_time_ms = 1000;

void setup()
{
    init_led();
    keypad.begin();
    Keyboard.begin();
}

// Main program loop.
void loop()
{
    // Keypad interaction
    char key_result = keypad.process();
    handle_keypress(key_result);

    // Process led. Do after keypress to immediately process color changes.
    led_manager.process();
}

void handle_keypress(char key_result)
{
    if (key_result == Keypad::key_release)
    {
        Keyboard.releaseAll();
    }
    else if(key_result != Keypad::no_key)
    {
        Keyboard.press(key_result);

        const LookUpTable* lut = map_key_to_color(key_result);
        if (lut)
        {
            led_manager.set(*lut, animation_time_ms);
        }
    }
}
