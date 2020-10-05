#include "SC18IS602RK.h"

SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(MANUAL);

SerialLogHandler logHandler;

SC18IS602 bridge;

void setup() {
    bridge.begin();
}

void loop() {
    
}

HAL_I2C_Config acquireWireBuffer() {
    return SC18IS602::getWireBuffer();
}

