#ifndef _SCOTTZ0R_HW_CFG_INCLUDE_GUARD
#define _SCOTTZ0R_HW_CFG_INCLUDE_GUARD

#include <Arduino.h>
#include "prj_generic_types.h"

// PWM pins for RGB LED
static constexpr int RED_LED = 9;
static constexpr int GREEN_LED = 10;
static constexpr int BLUE_LED = 11;

// Pins for the rows of the keypad. Pins 1-4 on the FP Keypad PCB.
static const int keypad_row_pins[] = {A0, A1, A2, A3};

// Pins for the columns of the keypad. Pins 5-11 on the FP Keypad PCB.
static const int keypad_col_pins[] = {A4, A5, 15, 16, 14, 7, 5};

// Pin used as a killswitch, which disables keyboard output. Use this if the keypad is misbehaving and it neeeds to
// be reflashed.
static constexpr int killswitch_pin = 12;


#endif // _SCOTTZ0R_HW_CFG_INCLUDE_GUARD
