/**
 * @file constants.h
 * @author argawaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

namespace sbs::physic {

/**
 * @brief List of known constant
 */
enum struct Constant {
    M_AirMeanMolarMass,            ///< Mean Molar mass of the Air (kg/mol)
    G_MeanEarthGravityAcceleration,///< Mean gravity acceleration on earth (m/s^2)
    R_PerfectGaz,                  ///< Universal constant of perfect gaz (J/K/mol)
    T0_WaterIceTemperature,        ///< Ice-water transition temperature (K)
};

/**
 * @brief Get the constant value as double
 * @param which Which constant to you want
 * @return The constant value
 */
inline double getConstant(const Constant& which) {
    double result = 0;
    switch (which) {
    case sbs::physic::Constant::M_AirMeanMolarMass:
        result = 0.0289644;
        break;
    case sbs::physic::Constant::G_MeanEarthGravityAcceleration:
        result = 9.80665;
        break;
    case sbs::physic::Constant::R_PerfectGaz:
        result = 8.31446261815;
        break;
    case sbs::physic::Constant::T0_WaterIceTemperature:
        result = 273.15;
    }
    return result;
}

}// namespace sbs::physic
