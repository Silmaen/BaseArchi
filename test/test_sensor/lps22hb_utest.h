/**
 * @file bme280_utest.h
 * @author argawaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once
#include <unity.h>

void lps22hb_base();

void lps22hb_emulated();

void bme280_settings();

void lps22hb_result();

void run_lps22hb(){
    RUN_TEST(lps22hb_base);
    RUN_TEST(lps22hb_emulated);
    RUN_TEST(lps22hb_result);
}
