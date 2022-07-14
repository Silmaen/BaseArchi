/**
 * @file bme280_utest.h
 * @author Silmaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once
#include <unity.h>

void veml6075_base();

void veml6075_emulated();

void veml6075_result();

void run_veml6075(){
    RUN_TEST(veml6075_base);
    RUN_TEST(veml6075_emulated);
    RUN_TEST(veml6075_result);
}
