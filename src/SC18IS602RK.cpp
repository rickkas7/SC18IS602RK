#include "SC18IS602RK.h"

static uint8_t _wireRxBuf[SC18IS602::WIRE_BUF_SIZE];
static uint8_t _wireTxBuf[SC18IS602::WIRE_BUF_SIZE]; 


SC18IS602::SC18IS602(TwoWire &wire, uint8_t i2caddr) : wire(wire), i2caddr(i2caddr) {
    if (i2caddr < 8) {
        // i2cAddr is 0x28 to 0x2f, but you can pass 0-7 for the  i2cAddr parameter
        i2caddr |= 0x28;
    }
}

SC18IS602::~SC18IS602() {
}


void SC18IS602::begin(bool callWireBegin) {
    if (callWireBegin) {
        wire.begin();
    }
}

bool SC18IS602::readData(uint8_t *data, size_t dataLen) {
    bool bResult = false;

    lock();

    wire.requestFrom(i2caddr, dataLen);

    if (wire.available() == (int)dataLen) {
        for(size_t ii = 0; ii < dataLen; ii++) {
            data[ii] = wire.read();
        }
        bResult = true;

    }

    unlock();

    return bResult;
}

uint8_t SC18IS602::writeData(uint8_t function, const uint8_t *data, size_t dataLen) {
    uint8_t res = 0;

    lock();

    wire.beginTransmission(i2caddr);

    wire.write(function);
    if (data) {
        for(size_t ii = 0; ii < dataLen; ii++) {
            wire.write(data[dataLen]);
        }
    }
    else {
        for(size_t ii = 0; ii < dataLen; ii++) {
            wire.write(0);
        }
    }
    res = wire.endTransmission(true);

    unlock();

    return res;
}


bool SC18IS602::configureSpi(uint32_t clock, uint8_t bitOrder, uint8_t dataMode) {
    bool bResult = true;
    uint8_t config = 0x00;

    if (clock >= SPEED_1843_KHZ) {
        // F1-F0 = 0b00
    }
    else
    if (clock >= SPEED_461_KHZ) {
        // F1-F0 = 0b01
        config |= 0x1;
    }
    else
    if (clock >= SPEED_115_KHZ) {
        // F1-F0 = 0b10
        config |= 0x2;
    }
    else { // SPEED_58_KHZ
        // F1-F0 = 0b11
        config |= 0x3;
    }

    config |= (dataMode & 0x3) << 2;

    if (dataMode == LSBFIRST) {
        config |= 0x20;
    }
    
    if (config != lastSpiConfig) {
        writeData(REG_SPI_CONFIG, &config, 1);

        lastSpiConfig = config;;
    }
    return bResult;
}

// [static]
HAL_I2C_Config SC18IS602::getWireBuffer() {
    HAL_I2C_Config config = {
        .size = sizeof(HAL_I2C_Config),
        .version = HAL_I2C_CONFIG_VERSION_1,
        .rx_buffer = _wireRxBuf,
        .rx_buffer_size = SC18IS602::WIRE_BUF_SIZE,
        .tx_buffer = _wireTxBuf,
        .tx_buffer_size = SC18IS602::WIRE_BUF_SIZE
    };
    return config;
}
