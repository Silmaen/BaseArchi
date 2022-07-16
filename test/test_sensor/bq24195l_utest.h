/**
 * @file bq24195l_utest.h
 * @author Silmaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

void bq24195l_base();

void bq24195l_emulated();

void bq24195l_settings();

void run_bq24195l(){
    RUN_TEST(bq24195l_base);
    RUN_TEST(bq24195l_emulated);
    RUN_TEST(bq24195l_settings);
}
