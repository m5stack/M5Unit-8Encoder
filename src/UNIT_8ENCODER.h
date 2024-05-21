#ifndef __UNIT_8ENCODER_H
#define __UNIT_8ENCODER_H

#include "Arduino.h"
#include "Wire.h"

#define ENCODER_ADDR         0x41
#define ENCODER_REG          0x00
#define INCREMENT_REG        0x20
#define BUTTON_REG           0x50
#define SWITCH_REG           0x60
#define RGB_LED_REG          0x70
#define RESET_COUNTER_REG    0x40
#define FIRMWARE_VERSION_REG 0xFE
#define I2C_ADDRESS_REG      0xFF

class UNIT_8ENCODER {
   private:
    uint8_t _addr;
    TwoWire* _wire;
    uint8_t _scl;
    uint8_t _sda;
    uint8_t _speed;
    void writeBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);
    void readBytes(uint8_t addr, uint8_t reg, uint8_t* buffer, uint8_t length);

   public:
    bool begin(TwoWire* wire = &Wire, uint8_t addr = ENCODER_ADDR,
               uint8_t sda = 21, uint8_t scl = 22, uint32_t speed = 100000L);
    uint32_t getEncoderValue(uint8_t index);
    void setEncoderValue(uint8_t index, int32_t value);
    int32_t getIncrementValue(uint8_t index);
    bool getButtonStatus(uint8_t index);
    bool getSwitchStatus(void);
    void setLEDColor(uint8_t index, uint32_t color);
    void setAllLEDColor(uint32_t color);
    uint8_t setI2CAddress(uint8_t addr);
    uint8_t getI2CAddress(void);
    uint8_t getFirmwareVersion(void);
    void resetCounter(uint8_t index);
};

#endif
