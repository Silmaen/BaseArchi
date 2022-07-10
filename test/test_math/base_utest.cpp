/**
 * @file base_utest.cpp
 * @author argawaen
 * @date 08/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include <math/base.h>

void basic_test(){
    TEST_ASSERT_DOUBLE_WITHIN(0.00001,10,sbs::math::min(15,10));
    TEST_ASSERT_DOUBLE_WITHIN(0.00001,10,sbs::math::min(10,15));
    TEST_ASSERT_DOUBLE_WITHIN(0.00001,10,sbs::math::max(5,10));
    TEST_ASSERT_DOUBLE_WITHIN(0.00001,10,sbs::math::max(10,5));
    TEST_ASSERT_DOUBLE_WITHIN(0.00001,10,sbs::math::clamp(48,5,10));
    TEST_ASSERT_DOUBLE_WITHIN(0.00001,5,sbs::math::clamp(4,5,10));
    TEST_ASSERT_DOUBLE_WITHIN(0.00001,8,sbs::math::clamp(8,5,10));
    TEST_ASSERT_DOUBLE_WITHIN(0.00001,5,sbs::math::clamp(48,10,5));
    TEST_ASSERT_DOUBLE_WITHIN(0.00001,5,sbs::math::clamp(4,10,5));
    TEST_ASSERT_DOUBLE_WITHIN(0.00001,5,sbs::math::clamp(8,10,5));
}
