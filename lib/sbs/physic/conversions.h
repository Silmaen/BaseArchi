/**
 * @file conversions.h
 * @author argawaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

/**
 * @brief Namespace for physics functions
 */
namespace sbs::physic {

/**
 * @brief Convert celsius temperature to kelvin
 * @param temperature Temperature in celsius
 * @return Temperature in kelvin
 */
double celsiusToKelvin(double temperature);

/**
 * @brief Compute actual altitude base on QNH value
 * @param qnh Mean sea level corrected pressure
 * @param measuredPressure Sensor measured pressure
 * @param measuredTemperature Sensor Measured Temperature
 * @return Altitude of the sensor above MSL
 */
double getAltitude(double qnh, double measuredPressure, double measuredTemperature);

/**
 * @brief Compute mean sea level corrected pressure based on precise sensor altitude.
 * @param sensorAltitude Sensor known altitude
 * @param measuredPressure Sensor measured pressure
 * @param measuredTemperature Sensor Measured Temperature
 * @return The MSL-corrected pressure
 */
double computeQnh(double sensorAltitude, double measuredPressure, double measuredTemperature);

}// namespace sbs::physic
