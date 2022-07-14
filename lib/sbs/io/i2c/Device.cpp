/**
 * @file Device.cpp
 * @author Silmaen
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "Device.h"

#ifdef ARDUINO
#include <Wire.h>
#endif

namespace sbs::io::i2c {

void Device::setAddress(uint8_t _address) {
    address = _address;
    selfCheck();
}
void Device::init() {
    baseDevice::init();
#ifdef ARDUINO
    Wire.begin();
#endif
}

}// namespace sbs::io::i2c
