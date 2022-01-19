// Author: Scott Clewell
// January 2022
// Program to turn a Fisher Price "Smart Stages" tablet into a HID Keyboard device.
// Requires a custom PBC (which I have conveniently designed) to replace the PCB that comes with the Keypad.
#include <Keyboard.h>
#include <avr/pgmspace.h>

// Define this macro to enable keyboard support. If not defined, the Serial will be used. Useful for debugging.
#define USE_KEYBOARD

using time_type = unsigned long;

#define scz_array_size(a) (sizeof(a)/sizeof(a[0]))

static constexpr time_type POLL_RATE = 30; // Rate at which the keypad will be polled.
static constexpr int NO_BUTTON = -1; // Represents when a button is not pressed.

// Pins for the rows of the keypad. Pins 1-4 on the FP Keypad PCB.
static const int row_pins[] = {A0, A1, A2, A3};
static constexpr int row_pins_count = scz_array_size(row_pins);

// Pins for the columns of the keypad. Pins 5-11 on the FP Keypad PCB.
static const int col_pins[] = {A4, A5, 15, 16, 14, 10, 9};
static constexpr int col_pins_count = scz_array_size(col_pins);

// Pin used as a killswitch, which disables keyboard output. Use this if the keypad is misbehaving and it neeeds to
// be reflashed.
static constexpr int killswitch_pin = 12;

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

static constexpr int keymap_size = scz_array_size(keymap);

static int prev_key_code = NO_BUTTON; // The last key pressed.

void setup()
{
    // Rows set as output, set high.
    for (int i = 0; i < row_pins_count; ++i)
    {
        pinMode(row_pins[i], OUTPUT);
        digitalWrite(row_pins[i], HIGH);  
    }

    // Columns input with pullup (Low = on)
    for (int i = 0; i < col_pins_count; ++i)
    {
        pinMode(col_pins[i], INPUT_PULLUP);
    }

    // Set killswitch as input pulled up. If connected to ground, it will disable the keyboard.
    pinMode(killswitch_pin, INPUT_PULLUP);

#ifdef USE_KEYBOARD
    Keyboard.begin();
#else
    Serial.begin(9600);
    Serial.println("Debug mode!");
#endif
}

// Main program loop.
void loop()
{
    time_type start = millis();

    int key = scan_pad();

    if (key >= 0 && key < keymap_size)
    {
        handle_keydown(key);
    }
    else
    {
        // No key pressed. Clear last key.
        prev_key_code = NO_BUTTON;

#ifdef USE_KEYBOARD
        // No key pressed, release all on the keyboard.
        Keyboard.releaseAll();
#endif
    }

    // Delay for the poll rate minus the processing time.
    time_type end = millis();
    time_type delay_amt = POLL_RATE - (end - start);
    delay(delay_amt);
}

// Scan the keypad for a pressed button. This will return after finding the first button pressed.
// This assumes the columns are inputs with pullups and the rows are outputs.
int scan_pad()
{
    int result = NO_BUTTON;

    for (int r = 0; r < row_pins_count; ++r)
    {
        // Write row low.
        int row_pin = row_pins[r];
        digitalWrite(row_pin, LOW);

        // Read columns to see if any are pulled low.
        for (int c = 0; c < col_pins_count; ++c)
        {
            int col_pin = col_pins[c];
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
void handle_keydown(int key_code)
{
    // Killswitch low = keyboard disabled.
    int is_killed = digitalRead(killswitch_pin);
    if (!is_killed)
    {
        return;
    }

    // Do nothing if the same key is pressed.
    if (prev_key_code == key_code)
    {
        return;
    }

    // Get ASCII character representation.
    char c = (char)pgm_read_byte_near(keymap + key_code);

    // Save last key press to avoid double pressing. This also helps with debounce, too.
    prev_key_code = key_code;

#ifdef USE_KEYBOARD
    // Send keypress
    Keyboard.press(c);
#else
    Serial.write(c);
#endif
}
