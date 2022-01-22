// Author: Scott Clewell
// January 2022
// Program to turn a Fisher Price "Smart Stages" tablet into a HID Keyboard device.
// Requires a custom PBC (which I have conveniently designed) to replace the PCB that comes with the Keypad.
#include "prj_generic_types.h"

#include "color_manager.h"
#include "globals.h"

using namespace scottz0r;

void setup()
{
    colorman::begin();
    keypad.begin();
}

// Main program loop.
void loop()
{
    keypad.process();
    led_manager.process();
}
