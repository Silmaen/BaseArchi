/**
 * @file MKREnv.cpp
 * @author Silmaen
 * @date 14/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "MKREnv.h"

namespace sbs::shield {

void MKREnv::Init() {
    humidityTemperature.init();
    pressureTemperature.init();
    UVSense.init();
}

const MKREnv::ShieldData& MKREnv::getValue() {
    auto tmpHum = humidityTemperature.getValue();
    auto tmpPres = pressureTemperature.getValue();
    auto UV = UVSense.getValue();
    data.Humidity = tmpHum.humidity;
    data.Temperature = (tmpHum.temperature + tmpPres.temperature) * 0.5;
    data.Pressure = tmpPres.pressure;
    data.UVa = UV.uva;
    data.UVb = UV.uvb;
    return data;
}

}// namespace sbs::shield
