/**
 * @file string_utest.cpp
 * @author damien.lachouette 
 * @date 06/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include <core/string.h>

void basic_test(){
    sbs::string str;
    TEST_ASSERT_EQUAL(0, str.size());
    TEST_ASSERT(str.empty());

}
