/**
 * @file device_utest.h
 * @author Silmaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once

void device_base_tests();
void device_i2c_base_tests();
void i2c_base_tests();
void i2c_emulated_tests();

void run_device(){
    RUN_TEST(device_base_tests);
    RUN_TEST(device_i2c_base_tests);
    RUN_TEST(i2c_base_tests);
    RUN_TEST(i2c_emulated_tests);
}
