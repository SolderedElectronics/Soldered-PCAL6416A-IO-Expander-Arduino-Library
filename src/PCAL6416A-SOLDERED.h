/**
 **************************************************
 *
 * @file        PCAL6416A-SOLDERED.h
 * @brief       Header file for sensor specific code.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Goran Juric @ soldered.com
 ***************************************************/

#ifndef __PCAL6416A__
#define __PCAL6416A__

#include "Arduino.h"
#include "libs/Generic-easyC/easyC.hpp"

// PCAL6416A Register map
#define PCAL6416A_BASE_ADDR 0x21

#define PCAL6416A_INPORT0        0x00
#define PCAL6416A_INPORT1        0x01
#define PCAL6416A_OUTPORT0       0x02
#define PCAL6416A_OUTPORT1       0x03
#define PCAL6416A_POLINVPORT0    0x04
#define PCAL6416A_POLINVPORT1    0x05
#define PCAL6416A_CFGPORT0       0x06
#define PCAL6416A_CFGPORT1       0x07
#define PCAL6416A_OUTDRVST_REG00 0x40
#define PCAL6416A_OUTDRVST_REG01 0x41
#define PCAL6416A_OUTDRVST_REG10 0x42
#define PCAL6416A_OUTDRVST_REG11 0x43
#define PCAL6416A_INLAT_REG0     0x44
#define PCAL6416A_INLAT_REG1     0x45
#define PCAL6416A_PUPDEN_REG0    0x46
#define PCAL6416A_PUPDEN_REG1    0x47
#define PCAL6416A_PUPDSEL_REG0   0x48
#define PCAL6416A_PUPDSEL_REG1   0x49
#define PCAL6416A_INTMSK_REG0    0x4A
#define PCAL6416A_INTMSK_REG1    0x4B
#define PCAL6416A_INTSTAT_REG0   0x4C
#define PCAL6416A_INTSTAT_REG1   0x4D
#define PCAL6416A_OUTPORT_CONF   0x4F

#define PCAL6416A_INPORT0_ARRAY        0
#define PCAL6416A_INPORT1_ARRAY        1
#define PCAL6416A_OUTPORT0_ARRAY       2
#define PCAL6416A_OUTPORT1_ARRAY       3
#define PCAL6416A_POLINVPORT0_ARRAY    4
#define PCAL6416A_POLINVPORT1_ARRAY    5
#define PCAL6416A_CFGPORT0_ARRAY       6
#define PCAL6416A_CFGPORT1_ARRAY       7
#define PCAL6416A_OUTDRVST_REG00_ARRAY 8
#define PCAL6416A_OUTDRVST_REG01_ARRAY 9
#define PCAL6416A_OUTDRVST_REG10_ARRAY 10
#define PCAL6416A_OUTDRVST_REG11_ARRAY 11
#define PCAL6416A_INLAT_REG0_ARRAY     12
#define PCAL6416A_INLAT_REG1_ARRAY     13
#define PCAL6416A_PUPDEN_REG0_ARRAY    14
#define PCAL6416A_PUPDEN_REG1_ARRAY    15
#define PCAL6416A_PUPDSEL_REG0_ARRAY   16
#define PCAL6416A_PUPDSEL_REG1_ARRAY   17
#define PCAL6416A_INTMSK_REG0_ARRAY    18
#define PCAL6416A_INTMSK_REG1_ARRAY    19
#define PCAL6416A_INTSTAT_REG0_ARRAY   20
#define PCAL6416A_INTSTAT_REG1_ARRAY   21
#define PCAL6416A_OUTPORT_CONF_ARRAY   22

#define PCAL6416A_A0 0
#define PCAL6416A_A1 1
#define PCAL6416A_A2 2
#define PCAL6416A_A3 3
#define PCAL6416A_A4 4
#define PCAL6416A_A5 5
#define PCAL6416A_A6 6
#define PCAL6416A_A7 7
#define PCAL6416A_B0 8
#define PCAL6416A_B1 9
#define PCAL6416A_B2 10
#define PCAL6416A_B3 11
#define PCAL6416A_B4 12
#define PCAL6416A_B5 13
#define PCAL6416A_B6 14
#define PCAL6416A_B7 15

#define INPUT_PULLDOWN 3


// Index to PCAL6416A register addresses conversion
const uint8_t regAddresses[] = {
    PCAL6416A_INPORT0,        PCAL6416A_INPORT1,        PCAL6416A_OUTPORT0,       PCAL6416A_OUTPORT1,
    PCAL6416A_POLINVPORT0,    PCAL6416A_POLINVPORT1,    PCAL6416A_CFGPORT0,       PCAL6416A_CFGPORT1,
    PCAL6416A_OUTDRVST_REG00, PCAL6416A_OUTDRVST_REG01, PCAL6416A_OUTDRVST_REG10, PCAL6416A_OUTDRVST_REG11,
    PCAL6416A_INLAT_REG0,     PCAL6416A_INLAT_REG1,     PCAL6416A_PUPDEN_REG0,    PCAL6416A_PUPDEN_REG1,
    PCAL6416A_PUPDSEL_REG0,   PCAL6416A_PUPDSEL_REG1,   PCAL6416A_INTMSK_REG0,    PCAL6416A_INTMSK_REG1,
    PCAL6416A_INTSTAT_REG0,   PCAL6416A_INTSTAT_REG1,   PCAL6416A_OUTPORT_CONF};

class PCAL6416A : public EasyC
{
  public:
    PCAL6416A();
    void pinModePCAL(uint8_t _pin, uint8_t _mode);
    void digitalWritePCAL(uint8_t _pin, uint8_t _state);
    void pinPolarityPCAL(uint8_t _pin, uint8_t _state);
    uint8_t digitalReadPCAL(uint8_t _pin);
    void driveStrengthPCAL(uint8_t _pin, uint8_t _str);
    void setInterruptPCAL(uint8_t _pin, uint8_t _en);
    uint16_t getInterruptsPCAL();
    void inputLatchingPCAL(uint8_t _pin, uint8_t _en);
    void openDrainPortPCAL(uint8_t _port, uint8_t _en);

  protected:
    void initializeNative();

  private:
    void writeReg(uint8_t _reg, uint8_t _data);
    void readReg(uint8_t _reg, uint8_t *_data);
    void getRegs(uint8_t *_data);
    void updateRegs(uint8_t *_data);
    uint8_t regs[23];
};

#endif
