/**
 **************************************************
 *
 * @file        PCAL6416A-SOLDERED.cpp
 * @brief       Example functions to overload in base class.
 *
 *
 * @copyright GNU General Public License v3.0
 * @authors     Goran Juric @ soldered.com
 ***************************************************/


#include "PCAL6416A-SOLDERED.h"

/**
 * @brief                   Default constructor for class.
 *
 */
PCAL6416A::PCAL6416A()
{
}

/**
 * @brief                   Not used here, but it needs to be defined
 *                          because it is virtual function.
 *
 */
void PCAL6416A::initializeNative()
{
}
/**
 * @brief                   Set pin config.
 *
 * @param _pin              Wanted pin. (0-15)
 *
 * @param _mode             Mode for pin operation (INPUT, INPUT_PULLUP, INPUT_PULLDOWN, OUTPUT)
 *
 */
void PCAL6416A::pinModePCAL(uint8_t _pin, uint8_t _mode)
{
    if (_pin > 15)
        return;

    uint8_t _port = _pin / 8;
    _pin %= 8;

    switch (_mode)
    {
    case INPUT:
        regs[PCAL6416A_CFGPORT0_ARRAY + _port] |= (1 << _pin);
        writeReg(PCAL6416A_CFGPORT0 + _port, regs[PCAL6416A_CFGPORT0_ARRAY + _port]);
        break;
    case OUTPUT:
        // There is a one cacth! Pins are by default (POR) set as HIGH. So first change it to LOW and then set is as
        // output).
        regs[PCAL6416A_CFGPORT0_ARRAY + _port] &= ~(1 << _pin);
        regs[PCAL6416A_OUTPORT0_ARRAY + _port] &= ~(1 << _pin);
        writeReg(PCAL6416A_OUTPORT0 + _port, regs[PCAL6416A_OUTPORT0_ARRAY + _port]);
        writeReg(PCAL6416A_CFGPORT0 + _port, regs[PCAL6416A_CFGPORT0_ARRAY + _port]);
        break;
    case INPUT_PULLUP:
        regs[PCAL6416A_CFGPORT0_ARRAY + _port] |= (1 << _pin);
        regs[PCAL6416A_PUPDEN_REG0_ARRAY + _port] |= (1 << _pin);
        regs[PCAL6416A_PUPDSEL_REG0_ARRAY + _port] |= (1 << _pin);
        writeReg(PCAL6416A_CFGPORT0 + _port, regs[PCAL6416A_CFGPORT0_ARRAY + _port]);
        writeReg(PCAL6416A_PUPDEN_REG0 + _port, regs[PCAL6416A_PUPDEN_REG0_ARRAY + _port]);
        writeReg(PCAL6416A_PUPDSEL_REG0 + _port, regs[PCAL6416A_PUPDSEL_REG0_ARRAY + _port]);
        break;
    case INPUT_PULLDOWN:
        regs[PCAL6416A_CFGPORT0_ARRAY + _port] |= (1 << _pin);
        regs[PCAL6416A_PUPDEN_REG0_ARRAY + _port] |= (1 << _pin);
        regs[PCAL6416A_PUPDSEL_REG0_ARRAY + _port] &= ~(1 << _pin);
        writeReg(PCAL6416A_CFGPORT0 + _port, regs[PCAL6416A_CFGPORT0_ARRAY + _port]);
        writeReg(PCAL6416A_PUPDEN_REG0 + _port, regs[PCAL6416A_PUPDEN_REG0_ARRAY + _port]);
        writeReg(PCAL6416A_PUPDSEL_REG0 + _port, regs[PCAL6416A_PUPDSEL_REG0_ARRAY + _port]);
        break;
    }
}

/**
 * @brief                   Set digital state on selected pin.
 *
 * @param _pin              Wanted pin.
 *
 * @param _state            State of pin (LOW, HIGH).
 */
void PCAL6416A::digitalWritePCAL(uint8_t _pin, uint8_t _state)
{
    if (_pin > 15)
        return;
    _state &= 1;

    uint8_t _port = _pin / 8;
    _pin %= 8;

    _state ? regs[PCAL6416A_OUTPORT0_ARRAY + _port] |= (1 << _pin)
           : regs[PCAL6416A_OUTPORT0_ARRAY + _port] &= ~(1 << _pin);
    writeReg(PCAL6416A_OUTPORT0 + _port, regs[PCAL6416A_OUTPORT0_ARRAY + _port]);
}

/**
 * @brief                   Change polarity on pin (valid only if selected pin is input pin)
 *
 * @param _pin              Wanted pin.
 *
 * @param _state            State of pin.
 */
void PCAL6416A::pinPolarityPCAL(uint8_t _pin, uint8_t _state)
{
    if (_pin > 15)
        return;
    _state &= 1;

    uint8_t _port = _pin / 8;
    _pin %= 8;

    _state ? regs[PCAL6416A_POLINVPORT0_ARRAY + _port] |= (1 << _pin)
           : regs[PCAL6416A_POLINVPORT0_ARRAY + _port] &= ~(1 << _pin);
    writeReg(PCAL6416A_POLINVPORT0 + _port, regs[PCAL6416A_POLINVPORT0_ARRAY + _port]);
}

/**
 * @brief                   Read state of the pin.
 *
 * @param _pin              Wanted pin.
 *
 * @return uint8_t          Return state on selected pin. 0 = LOW, 1 = HIGH, -1 = wrong pin
 */
uint8_t PCAL6416A::digitalReadPCAL(uint8_t _pin)
{
    if (_pin > 15)
        return -1;

    uint8_t _port = _pin / 8;
    _pin %= 8;

    readReg(PCAL6416A_INPORT0 + _port, &regs[PCAL6416A_INPORT0_ARRAY + _port]);

    return ((regs[PCAL6416A_INPORT0_ARRAY + _port] >> _pin) & 1);
}

/**
 * @brief                   Set drive strength on selected pin.
 *
 * @param _pin              Wanted pin.
 *
 * @param _str              There are four level of strenght (_str = 00 -> weakest, _str = 11 -> strongest)
 */
void PCAL6416A::driveStrengthPCAL(uint8_t _pin, uint8_t _str)
{
    if (_pin > 15)
        return;

    uint8_t _reg = _pin / 4;
    _pin %= 4;
    _str &= 3;

    regs[PCAL6416A_OUTDRVST_REG00_ARRAY + _reg] &= ~(3 << _pin);
    regs[PCAL6416A_OUTDRVST_REG00_ARRAY + _reg] |= (_str << _pin);

    writeReg(PCAL6416A_OUTDRVST_REG00 + _reg, regs[PCAL6416A_OUTDRVST_REG00_ARRAY + _reg]);
}

/**
 * @brief                   Enable or disable Interrupt on specific pin.
 *
 * @param _pin              Wanted pin.
 *
 * @param _en               To enable interrupt set to 1, to disable set to 0
 */
void PCAL6416A::setInterruptPCAL(uint8_t _pin, uint8_t _en)
{
    if (_pin > 15)
        return;

    uint8_t _port = _pin / 8;
    _pin %= 8;

    _en ? regs[PCAL6416A_INTMSK_REG0_ARRAY + _port] &= ~(1 << _pin)
        : regs[PCAL6416A_INTMSK_REG0_ARRAY + _port] |= (1 << _pin);

    writeReg(PCAL6416A_INTMSK_REG0 + _port, regs[PCAL6416A_INTMSK_REG0_ARRAY + _port]);
}

/**
 * @brief                   Read status register of detected interrupts.
 *
 * @return uint16_t         State of detected interrupt registers.
 */
uint16_t PCAL6416A::getInterruptsPCAL()
{
    readReg(PCAL6416A_INTSTAT_REG0, &regs[PCAL6416A_INTSTAT_REG0_ARRAY]);
    readReg(PCAL6416A_INTSTAT_REG1, &regs[PCAL6416A_INTSTAT_REG1_ARRAY]);

    return ((regs[PCAL6416A_INTSTAT_REG1_ARRAY] << 8) | (regs[PCAL6416A_INTSTAT_REG0_ARRAY]));
}

/**
 * @brief                   Enable latching on selected pin.
 *
 * @param _pin              Wanted pin.
 *
 * @param _en               Enable or disable latching (0 or 1).
 */
void PCAL6416A::inputLatchingPCAL(uint8_t _pin, uint8_t _en)
{
    if (_pin > 15)
        return;

    uint8_t _port = _pin / 8;
    _pin %= 8;

    _en ? regs[PCAL6416A_INLAT_REG0_ARRAY + _port] |= (1 << _pin)
        : regs[PCAL6416A_INLAT_REG0_ARRAY + _port] &= ~(1 << _pin);

    writeReg(PCAL6416A_INLAT_REG0 + _port, regs[PCAL6416A_INLAT_REG0_ARRAY + _port]);
}

/**
 * @brief                   Set whole port as open drain.
 *
 * @param _port             Port 0 or port 1.
 *
 * @param _en               Enable or disable open drain port (0 or 1).
 */
void PCAL6416A::openDrainPortPCAL(uint8_t _port, uint8_t _en)
{
    _port &= 1;

    _en ? regs[PCAL6416A_OUTPORT_CONF_ARRAY] |= (1 << _port) : regs[PCAL6416A_OUTPORT_CONF_ARRAY] &= ~(1 << _port);

    writeReg(PCAL6416A_OUTPORT_CONF, regs[PCAL6416A_OUTPORT_CONF_ARRAY]);
}

// PRIVATE

/**
 * @brief                   Write data to single register.
 *
 * @param _reg              Register to write.
 *
 * @param _data             Data to write.
 */
void PCAL6416A::writeReg(uint8_t _reg, uint8_t _data)
{
    uint8_t temp[2];
    temp[0] = _reg;
    temp[1] = _data;
    sendData(temp, 2);
}

/**
 * @brief                   Read single register.
 *
 * @param _reg              Register to read.
 *
 * @param _data             Variable to store read data.
 */
void PCAL6416A::readReg(uint8_t _reg, uint8_t *_data)
{
    readRegister(_reg, (char *)_data, 1);
}

/**
 * @brief                   Read data from all PCAL6416A registers and store it in array.
 *
 * @param _data             Array to store data from PCAL6416A.
 */
void PCAL6416A::getRegs(uint8_t *_data)
{
    for (int i = 0; i < 23; i++)
    {
        readReg(regAddresses[i], &_data[i]);
    }
}

/**
 * @brief                   Push all data from array into PCAL6416A registers
 *
 * @param _data             Array which contains data to push to PCAL6416A
 */
void PCAL6416A::updateRegs(uint8_t *_data)
{
    for (int i = 0; i < 23; i++)
    {
        writeReg(regAddresses[i], _data[i]);
    }
}