#ifndef __SC18IS602RK
#define __SC18IS602RK

#include "Particle.h"

class SC18IS602 {
public:
    SC18IS602(TwoWire &wire = Wire, uint8_t i2caddr = 0);
    virtual ~SC18IS602();

    void begin(bool callWireBegin = true);

    bool configureSpi(uint32_t clock, uint8_t bitOrder, uint8_t dataMode);

    bool readData(uint8_t *data, size_t dataLen);

    uint8_t writeData(uint8_t function, const uint8_t *data, size_t dataLen);

    void lock() { wire.lock(); };

    void unlock() { wire.unlock(); };

    static HAL_I2C_Config getWireBuffer();

    static const uint32_t SPEED_1843_KHZ = 1843000;
    static const uint32_t SPEED_461_KHZ = 461000;
    static const uint32_t SPEED_115_KHZ = 115000;
    static const uint32_t SPEED_58_KHZ = 58000;

    static const uint8_t REG_SPI_CONFIG = 0xf0;
    static const uint8_t REG_CLEAR_INT = 0xf1;
    static const uint8_t REG_IDLE = 0xf2;
    static const uint8_t REG_GPIO_WRITE = 0xf4;
    static const uint8_t REG_GPIO_READ = 0xf5;
    static const uint8_t REG_GPIO_ENABLE = 0xf6;
    static const uint8_t REG_GPIO_CONFIG = 0xf7;

    static const size_t WIRE_BUF_SIZE = 201;

protected:
    TwoWire &wire;
    uint8_t i2caddr;
    uint8_t lastSpiConfig = 0x00;
};




#endif /* SC18IS602RK */
