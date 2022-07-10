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
inline constexpr double getConstant(const Constant& which) {
    switch (which) {
    case sbs::physic::Constant::M_AirMeanMolarMass:
        return 0.0289644;
    case sbs::physic::Constant::G_MeanEarthGravityAcceleration:
        return 9.80665;
    case sbs::physic::Constant::R_PerfectGaz:
        return 8.31446261815;
    case sbs::physic::Constant::T0_WaterIceTemperature:
        return 273.15;
    }
    return 0;
}

}// namespace sbs::physic
