/**
 * @file base_utest.cpp
 * @author Silmean
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include <physic/conversions.h>
#include <physic/constants.h>

void constant_test(){
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 9.80665, sbs::physic::getConstant(sbs::physic::Constant::G_MeanEarthGravityAcceleration));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0289644, sbs::physic::getConstant(sbs::physic::Constant::M_AirMeanMolarMass));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 8.31446261815, sbs::physic::getConstant(sbs::physic::Constant::R_PerfectGaz));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 273.15, sbs::physic::getConstant(sbs::physic::Constant::T0_WaterIceTemperature));
    TEST_ASSERT_DOUBLE_WITHIN(0.0001, 0.0, sbs::physic::getConstant(sbs::physic::Constant{-1}));
};

void basicphysic_test(){
    TEST_ASSERT_DOUBLE_WITHIN(0.0001,298.15, sbs::physic::celsiusToKelvin(25));
    TEST_ASSERT_DOUBLE_WITHIN(0.001,300,sbs::physic::getAltitude(1020,986.0926125,30));
    TEST_ASSERT_DOUBLE_WITHIN(0.001,1020,sbs::physic::computeQnh(300,986.0926125,30));
}
