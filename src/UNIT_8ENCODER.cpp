#include "UNIT_8ENCODER.h"

void UNIT_8ENCODER::writeBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                               uint8_t length) {
    _wire->beginTransmission(addr);
    _wire->write(reg);
    for (int i = 0; i < length; i++) {
        _wire->write(*(buffer + i));
    }
    _wire->endTransmission();
}

void UNIT_8ENCODER::readBytes(uint8_t addr, uint8_t reg, uint8_t *buffer,
                              uint8_t length) {
    uint8_t index = 0;
    _wire->beginTransmission(addr);
    _wire->write(reg);
    _wire->endTransmission();
    _wire->requestFrom(addr, length);
    for (int i = 0; i < length; i++) {
        buffer[index++] = _wire->read();
    }
}

bool UNIT_8ENCODER::begin(TwoWire *wire, uint8_t addr, uint8_t sda, uint8_t scl,
                          uint32_t speed) {
    _wire  = wire;
    _addr  = addr;
    _sda   = sda;
    _scl   = scl;
    _speed = speed;
    _wire->begin(_sda, _scl, _speed);
    delay(10);
    _wire->beginTransmission(_addr);
    uint8_t error = _wire->endTransmission();
    if (error == 0) {
        return true;
    } else {
        return false;
    }
}

int32_t UNIT_8ENCODER::getEncoderValue(uint8_t index) {
    uint8_t data[4];
    uint8_t reg = index * 4 + ENCODER_REG;
    readBytes(_addr, reg, data, 4);
    int32_t value =
        data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    return value;
}

void UNIT_8ENCODER::setEncoderValue(uint8_t index, int32_t value) {
    uint8_t data[4];
    uint8_t reg = index * 4 + ENCODER_REG;

    data[0] = value & 0xff;
    data[1] = (value >> 8) & 0xff;
    data[2] = (value >> 16) & 0xff;
    data[3] = (value >> 24) & 0xff;
    writeBytes(_addr, reg, data, 4);
}

int32_t UNIT_8ENCODER::getIncrementValue(uint8_t index) {
    uint8_t data[4];
    uint8_t reg = index * 4 + INCREMENT_REG;
    readBytes(_addr, reg, data, 4);
    int32_t value =
        data[0] | (data[1] << 8) | (data[2] << 16) | (data[3] << 24);
    return value;
}

bool UNIT_8ENCODER::getButtonStatus(uint8_t index) {
    uint8_t data;
    uint8_t reg = index + BUTTON_REG;
    readBytes(_addr, reg, &data, 1);
    return data;
}

bool UNIT_8ENCODER::getSwitchStatus(void) {
    uint8_t data;
    readBytes(_addr, SWITCH_REG, &data, 1);
    return data;
}

void UNIT_8ENCODER::setLEDColor(uint8_t index, uint32_t color) {
    uint8_t data[4];
    data[2]     = color & 0xff;
    data[1]     = (color >> 8) & 0xff;
    data[0]     = (color >> 16) & 0xff;
    uint8_t reg = index * 3 + RGB_LED_REG;
    writeBytes(_addr, reg, data, 3);
}

void UNIT_8ENCODER::setAllLEDColor(uint32_t color) {
    uint8_t data[27];
    data[26] = color & 0xff;
    data[25] = (color >> 8) & 0xff;
    data[24] = (color >> 16) & 0xff;
    data[23] = color & 0xff;
    data[22] = (color >> 8) & 0xff;
    data[21] = (color >> 16) & 0xff;
    data[20] = color & 0xff;
    data[19] = (color >> 8) & 0xff;
    data[18] = (color >> 16) & 0xff;
    data[17] = color & 0xff;
    data[16] = (color >> 8) & 0xff;
    data[15] = (color >> 16) & 0xff;
    data[14] = color & 0xff;
    data[13] = (color >> 8) & 0xff;
    data[12] = (color >> 16) & 0xff;
    data[11] = color & 0xff;
    data[10] = (color >> 8) & 0xff;
    data[9]  = (color >> 16) & 0xff;
    data[8]  = color & 0xff;
    data[7]  = (color >> 8) & 0xff;
    data[6]  = (color >> 16) & 0xff;
    data[5]  = color & 0xff;
    data[4]  = (color >> 8) & 0xff;
    data[3]  = (color >> 16) & 0xff;
    data[2]  = color & 0xff;
    data[1]  = (color >> 8) & 0xff;
    data[0]  = (color >> 16) & 0xff;
    writeBytes(_addr, RGB_LED_REG, data, 27);
}

void UNIT_8ENCODER::resetCounter(uint8_t index) {
    uint8_t data[4];
    data[0]     = 1;
    uint8_t reg = index + RESET_COUNTER_REG;
    writeBytes(_addr, reg, data, 1);
}

uint8_t UNIT_8ENCODER::setI2CAddress(uint8_t addr) {
    _wire->beginTransmission(_addr);
    _wire->write(I2C_ADDRESS_REG);
    _wire->write(addr);
    _wire->endTransmission();
    _addr = addr;
    return _addr;
}

uint8_t UNIT_8ENCODER::getI2CAddress(void) {
    _wire->beginTransmission(_addr);
    _wire->write(I2C_ADDRESS_REG);
    _wire->endTransmission();

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1);
    RegValue = Wire.read();
    return RegValue;
}

uint8_t UNIT_8ENCODER::getFirmwareVersion(void) {
    _wire->beginTransmission(_addr);
    _wire->write(FIRMWARE_VERSION_REG);
    _wire->endTransmission();

    uint8_t RegValue;

    _wire->requestFrom(_addr, 1);
    RegValue = Wire.read();
    return RegValue;
}
