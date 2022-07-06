/**
 * @file test_arduino.cpp
 * @author Silmaen
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
  sbs::time::delay(10);
  auto deltaMilli = sbs::time::millis() - startMilli;
  auto deltaMicros = sbs::time::micros() - startMicros;
  auto deltaMicros64 = sbs::time::micros64() - startMicros64;
  TEST_ASSERT_UINT_WITHIN(1,10,deltaMilli);
  TEST_ASSERT_UINT_WITHIN(30,10030,deltaMicros);
  TEST_ASSERT_UINT_WITHIN(30,10030,deltaMicros64);
  sbs::time::delayMicroseconds(100);
  deltaMilli   = sbs::time::millis();
  deltaMicros   = sbs::time::micros();
  deltaMicros64 = sbs::time::micros64();
  TEST_ASSERT_UINT32_WITHIN(1, 10, deltaMilli);
  TEST_ASSERT_UINT32_WITHIN(60, 10160, deltaMicros);
  TEST_ASSERT_UINT32_WITHIN(60, 10160, deltaMicros64);
}

