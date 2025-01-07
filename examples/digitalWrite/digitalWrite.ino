/**
 **************************************************

    @file        digitalWrite.ino
    @brief       Example showing how to use digitalWrite
                function for PCAL6416 breakout board.



    @authors     Goran Juric @ soldered.com
 ***************************************************/

#include "PCAL6416A-SOLDERED.h"

PCAL6416A expander;   // Create object from class PCAL6416A

void setup()
{
    Serial.begin(115200); // Start serial communication with PC
                          // with baud rate of 115200 bauds per second

    expander.begin();     // Initialize PCAL6416A GPIO Expander, start
                          // I2C communication. This needs to be called
                          // only once before any other command
    // If you're setting a custom I2C address, use expander.begin(0x32)
    
    expander.pinModePCAL(PCAL6416A_A0, OUTPUT); // Set pin mode to output. Pins which are available
                                                // are pins PCAL6416A_A0 to PCAL6416A_A7 on port A
                                                // and pins PCAL6416A_B0 to PCAL6416A_B7 on port B.
                                                // This function sets pin to be input or output.
                                                // It can also be set to input with pullup or with
                                                // pulldown if needed, just instead of OUTPUT put
                                                // INPUT_PULLUP or INPUT_PULLDOWN.
}

void loop()
{
    expander.digitalWritePCAL(PCAL6416A_A0, HIGH);  // This function sets state of GPIO pin when pin is set to output.
                                                    // If set to HIGH pin will be internally pulled to HIGH level
                                                    // and can source small amount of current. If set to LOW it will
                                                    // be internally pulled to LOW level and can sink small amount
                                                    // of current. Same principle as Arduino's embedded functions.
    delay(1000);                                    // Wait a bit.
    expander.digitalWritePCAL(PCAL6416A_A0, LOW);   // Set GPIO pin to LOW level.
    delay(1000);                                    // Wait a bit.
}
