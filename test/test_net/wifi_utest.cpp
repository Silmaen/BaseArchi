/**
 * @file base_utest.cpp
 * @author Silmaen
 * @date 17/07/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */

#include "../test_helper.h"
#include <net/Wifi.h>

void wifi_base_test(){
    sbs::net::Wifi& wifi= sbs::net::Wifi::get();
    wifi.init("toto","caca");
    TEST_ASSERT_EQUAL(sbs::net::Wifi::Status::Unavailable, wifi.getStatus());
    TEST_ASSERT_TRUE(sbs::net::MacAddress{} == wifi.getBSSID());
    TEST_ASSERT_TRUE(sbs::net::MacAddress{} == wifi.getMAC());
    TEST_ASSERT_TRUE(sbs::net::IpAddress(127,0,0,1) == wifi.getLocalIP());
    TEST_ASSERT_TRUE(sbs::net::IpAddress(255,255,255,0) == wifi.getNetMask());
    TEST_ASSERT_TRUE(sbs::net::IpAddress(0,0,0,0) == wifi.getGateway());
    TEST_ASSERT_TRUE(sbs::net::IpAddress(0,0,0,0) == wifi.getDNS(0));
    TEST_ASSERT_EQUAL(0,wifi.getRSSI());
    TEST_ASSERT_EQUAL_STRING("",wifi.getSSID().c_str());
#ifdef NATIVE
    fakeWifiSetStatus(0);
    TEST_ASSERT_EQUAL(sbs::net::Wifi::Status::Disconnected, wifi.getStatus());
    fakeWifiSetStatus(3);
    TEST_ASSERT_EQUAL(sbs::net::Wifi::Status::ClientConnected, wifi.getStatus());
#endif
};
