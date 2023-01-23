/**
 *******************************************************

    @file       driveStrength.ino
    @brief      Example showing how to use driveStrength
                function for PCAL6416 breakout board.
                Drive strength sets number of output
                transistor pairs are driving output. 
                The more transistors driving output, the
                more current pin can sink or source. Also
                we will use openDrain function to set whole
                port to open drain. Unfortunatelly PCAL can
                set only whole port as open drain or high impedance
                state.
               


    @authors     Goran Juric @ soldered.com
 ********************************************************/

#include "PCAL6416A-SOLDERED.h"

PCAL6416A expander;   // Create object from class PCAL6416A

void setup()
{
    Serial.begin(115200); // Start serial communication with PC


    expander.begin();     // Initialize PCAL6416A GPIO Expander, start
                          // I2C communication. This needs to be called
                          // only once before any other command

    expander.pinModePCAL(PCAL6416A_A0, OUTPUT); // Set pin mode to input internally pulled HIGH.
                                                      // Pins which are available are pins PCAL6416A_A0
                                                      // to PCAL6416A_A7 on port A and pins PCAL6416A_B0
                                                      // to PCAL6416A_B7 on port B. This function sets
                                                      // pin to be input or output. If can also be set to
                                                      // input with pulldown if needed by using INPUT_PULLDOWN.

     expander.openDrainPortPCAL(1, 1);                // Set port B (port 1) to open drain, as we will not
                                                      // use it in this example. If port is set to open drain
                                                      // it means that if we set it to logical HIGH it will be
                                                      // disconnected from anything and if set to low it will be
                                                      // shorted to ground. So we need external pullup resistor.
                                                      // This is usefull when driving loads which needs to be
                                                      // disconnected from everything sometimes.
                                                     
                                                      
}

void loop()
{
    expander.digitalWritePCAL(PCAL6416A_A0, 1); // Set pin state to HIGH
    
    for(int i = 0; i < 4; i++)  // Loop through all possible iterations
    {
        expander.driveStrengthPCAL(PCAL6416A_A0, i);  // This function is used to set drive strength of output
                                                      // pin on this IO expander. As stated in example description
                                                      // drive strength tells us about number of transistor pairs
                                                      // driving the output. If we set bigger number here, the more
                                                      // current pin can sink or source. 
        delay(1000);
    }
    
}
