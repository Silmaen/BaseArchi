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

double computeDewPoint(double measuredTemperature, double measuredRelativeHumidity) {
    // Tr = b * alpha(T,Rh) / (a-alpha(T,Rh)
    // alpha(T,Rh) = aT/(b+T) + ln(Rh)
    /// cf. https://en.wikipedia.org/wiki/Dew_point
    constexpr double a_low  = 17.966;
    constexpr double a_high = 17.368;
    constexpr double b_low  = 247.15;
    constexpr double b_high = 238.88;
    if (measuredTemperature < 0) {
        double alpha = a_low * measuredTemperature / (b_low + measuredTemperature) + math::log(measuredRelativeHumidity / 100.0);
        return b_low * alpha / (a_low - alpha);
    }
    double alpha = a_high * measuredTemperature / (b_high + measuredTemperature) + math::log(measuredRelativeHumidity / 100.0);
    return b_high * alpha / (a_high - alpha);
}

}// namespace sbs::physic
