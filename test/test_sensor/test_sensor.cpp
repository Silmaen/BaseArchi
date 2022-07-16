/**
 * @file test_time.cpp
 * @author Silmaen
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "../test_base.h"
#include "bme280_utest.h"
#include "lps22hb_utest.h"
#include "device_utest.h"
#include "hts221_utest.h"
#include "veml6075_utest.h"
#include "bq24195l_utest.h"

int runtest(){
    UNITY_BEGIN();
    run_device();
    run_bme280();
    run_lps22hb();
    run_hts221();
    run_veml6075();
    run_bq24195l();
    return UNITY_END();
}
