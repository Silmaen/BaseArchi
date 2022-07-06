/**
 * @file test_arduino.cpp
 * @author argawaen
 * @date 09/01/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include <time/timing.h>

void timing() {
  auto startMilli = sbs::time::millis();
  auto startMicros = sbs::time::micros();
  auto startMicros64 = sbs::time::micros64();
  sbs::time::delay(1);
  sbs::time::delayMicroseconds(1);
  startMilli = sbs::time::millis() - startMilli;
  startMicros = sbs::time::micros() - startMicros;
  startMicros64 = sbs::time::micros64() - startMicros64;
  TEST_ASSERT_UINT_WITHIN(1,1,startMilli);
  TEST_ASSERT_UINT_WITHIN(10,1001,startMicros);
  TEST_ASSERT_UINT_WITHIN(10,1001,startMicros64);
}

