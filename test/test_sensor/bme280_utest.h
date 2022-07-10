/**
 * @file bme280_utest.h
 * @author argawaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

void bme280_base();

void bme280_emulated();

void bme280_settings();

void bme280_result();

void run_bme280(){
    RUN_TEST(bme280_base);
    RUN_TEST(bme280_emulated);
    RUN_TEST(bme280_settings);
    RUN_TEST(bme280_result);
}
