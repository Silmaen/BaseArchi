/**
* @file batteryMonitor_utest.h
* @author Silmaen
* @date 26/07/2022
* Copyright © 2022 All rights reserved.
* All modification must get authorization from the author.
*/

#pragma once
#include <unity.h>

void battmot_base();

void run_battmot(){
   RUN_TEST(battmot_base);
}
