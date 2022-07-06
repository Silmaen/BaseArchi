/**
 * @file Bme280.cpp
 * @author damien.lachouette 
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "Bme280.h"

namespace sbs::sensor {
constexpr uint8_t defaultAddress = 0;

BME280::BME280():
    io::i2c::Device{defaultAddress} {

}

}// namespace sbs::sensor