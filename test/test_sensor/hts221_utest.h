/**
 * @file bme280_utest.h
 * @author Silmean
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#pragma once
#include <unity.h>

void hts221_base();

void hts221_emulated();

void run_hts221(){
    RUN_TEST(hts221_base);
    RUN_TEST(hts221_emulated);
}
