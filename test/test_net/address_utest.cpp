/**
 * @file base_utest.cpp
 * @author Silmaen
 * @date 17/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include <net/Address.h>

void ipAddress_test(){
    sbs::net::IpAddress address;
    sbs::net::IpAddress address2{192,168,0,1};
    TEST_ASSERT_EQUAL(0,address.raw());
    TEST_ASSERT_TRUE(address != address2);
    TEST_ASSERT_FALSE(address == address2);
    TEST_ASSERT_FALSE(address.inSameNetwork(address2,{255,255,255,0}));
    address = sbs::net::IpAddress{address2.raw()};
    TEST_ASSERT_TRUE(address == address2);
};

void macAddress_test(){
    sbs::net::MacAddress address;
    sbs::net::MacAddress address2{0xFF,0x45,0x78,0xA3,0xFB,0x11};
    TEST_ASSERT_EQUAL(0,address.raw());
    TEST_ASSERT_TRUE(address != address2);
    TEST_ASSERT_FALSE(address == address2);
    address = sbs::net::MacAddress{address2.raw()};
    TEST_ASSERT_TRUE(address == address2);
}
