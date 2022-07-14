/**
 * @file mkrenv_utest.h
 * @author Silmaen
 * @date 14/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#pragma once
#include <unity.h>

void mkrenv_base();

void mkrenv_emulated();

void mkrenv_result();

void run_mkrenv(){
    RUN_TEST(mkrenv_base);
    RUN_TEST(mkrenv_emulated);
    RUN_TEST(mkrenv_result);
}
