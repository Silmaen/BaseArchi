/**
 * @file conversions.cpp
 * @author Silmaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "constants.h"
#include "math/functions.h"

namespace sbs::physic {

double celsiusToKelvin(double temperature) {
    return temperature + getConstant(Constant::T0_WaterIceTemperature);
}

/// Base coefficient for altitude computation
const double coef = -getConstant(Constant::R_PerfectGaz) / getConstant(Constant::G_MeanEarthGravityAcceleration) / getConstant(Constant::M_AirMeanMolarMass);

double getAltitude(double qnh, double measuredPressure, double measuredTemperature) {
    // h = -R*T/(µ*g). ln(P/P0)
    return coef * (celsiusToKelvin(measuredTemperature)) * math::log(measuredPressure / qnh);
}

double computeQnh(double sensorAltitude, double measuredPressure, double measuredTemperature) {
    // qnh = P * exp(µ*g*AltitudeRef / (R * T))
    return measuredPressure * math::exp(-sensorAltitude / coef / celsiusToKelvin(measuredTemperature));
}

}// namespace sbs::physic
