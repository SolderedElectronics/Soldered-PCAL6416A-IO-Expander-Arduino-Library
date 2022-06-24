/**
 **************************************************

    @file       digitalRead.ino
    @brief      Example showing how to use digitalRead
                function for PCAL6416 breakout board.
                For this example you will need to connect
                pushbutton to pin A0 and ground, so
                pushbutton can connect pin A0 to ground.


    @authors     Goran Juric @ soldered.com
 ***************************************************/

#include "PCAL6416A-SOLDERED.h"

PCAL6416A expander;   // Create object from class PCAL6416A

void setup()
{
    Serial.begin(115200); // Start serial communication with PC
                          

    expander.begin();     // Initialize PCAL6416A GPIO Expander, start
                          // I2C communication. This needs to be called
                          // only once before any other command

    expander.pinModePCAL(PCAL6416A_A0, INPUT_PULLUP); // Set pin mode to input internally pulled HIGH.
                                                      // Pins which are available are pins PCAL6416A_A0
                                                      // to PCAL6416A_A7 on port A and pins PCAL6416A_B0
                                                      // to PCAL6416A_B7 on port B. This function sets
                                                      // pin to be input or output. If can also be set to
                                                      // input with pulldown if needed by using INPUT_PULLDOWN.
}

void loop()
{
    Serial.print("State of pin A0 is: ");   // Print some information. 
    expander.digitalReadPCAL(PCAL6416A_A0) ? Serial.println("HIGH.") : Serial.println("LOW.") ; 
                                              // This function sets state of GPIO pin when pin is set to output.
                                              // If set to HIGH pin will be internally pulled to HIGH level
                                              // and can source small amount of current. If set to LOW it will
                                              // be internally pulled to LOW level and can sink small amount
                                              // of current. Same principle as Arduino's embedded functions.
                                              // Also this method is called ternary operator. It serves just like
                                              // if and else but it could be written in one line. If expression before
                                              // question mark is true, statement left from : will be executed, but if
                                              // expression is false, statement right of : will be executed.
                                              
    delay(1000);                              // Wait a bit.
}
