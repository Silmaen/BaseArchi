/**
 * @file base_utest.h
 * @author Silmaen
 * @date 17/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include <unity.h>

void wifi_base_test();

void run_wifi(){
    RUN_TEST(wifi_base_test);
}
