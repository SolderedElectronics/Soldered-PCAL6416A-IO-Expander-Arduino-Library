/**
 **************************************************

    @file       interrupts.ino
    @brief      Example showing how to use Interrupts
                for PCAL6416 breakout board.
                For this example you will need to connect
                one pushbutton to pin A0 and ground, so
                pushbutton can connect pin A0 to ground and
                to pin A1 in the same way like to A0.
                When pushbutton is pressed, Interrupt is
                fired and needs to be read. Also connect INT
                pin to pin D2 on your development board.
                PCAL6416A allows you only detecting interrupts
                on change, if you want to detect falling or rising
                edges, it needs to be done in code.


    @authors     Goran Juric @ soldered.com
 ***************************************************/

#include "PCAL6416A-SOLDERED.h"

PCAL6416A expander;   // Create object from class PCAL6416A

#define INT_PIN 2

bool intFlag = 0; // Flag needed to detect interrupts

// This is callback function. It is called only when interrupt is detected
// on interrupt pin. It should last as short as possible so we will here
// only set flag and do other stuff in loop.
void myISR()
{
    intFlag = 1;
}


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
    expander.pinModePCAL(PCAL6416A_A1, INPUT_PULLUP);

    pinMode(INT_PIN, INPUT_PULLUP); // Set INT pin on pin 2
    attachInterrupt(digitalPinToInterrupt(INT_PIN), myISR, FALLING); //Set interrupt on development board pin
    expander.setInterruptPCAL(PCAL6416A_A0, true); // Enable interrupts for specific pin on IO expander
    expander.setInterruptPCAL(PCAL6416A_A1, true); // Enable interrupts for specific pin on IO expander
}

void loop()
{
    if(intFlag)
    {
        intFlag = 0;  // Clear flag, so this function wouldn't loop always
        uint16_t intReg = expander.getInterruptsPCAL(); // Get state of interrupts registers
                                                        // It is needed to get whole register
                                                        // and extract information about pin
                                                        // we are interested in.
                                               
        if(intReg & 1 << PCAL6416A_A0)       // If interrupt happened on pin we are interested in
        {
            Serial.print("Interrupt detected on pin A0! Pin state is now: ");
            expander.digitalReadPCAL(PCAL6416A_A0) ? Serial.println("HIGH") : Serial.println("LOW");
                                                    // Check state of pin after interrupt happened and print
                                                    // it on Serial monitor. In example digitalRead is explained
                                                    // how this works.
            
        }

        if(intReg & 1 << PCAL6416A_A1)       // If interrupt happened on pin we are interested in
        {
            Serial.print("Interrupt detected on pin A1! Pin state is now: ");
            expander.digitalReadPCAL(PCAL6416A_A1) ? Serial.println("HIGH") : Serial.println("LOW");
                                                    // Check state of pin after interrupt happened and print
                                                    // it on Serial monitor. In example digitalRead is explained
                                                    // how this works.
            
        }
        
    }
}
