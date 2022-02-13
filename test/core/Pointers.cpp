/**
 * @file Pointers.cpp
 * @author argawaen
 * @date 13/02/2022
 * Copyright © 2022 All rights reserved.
 * All modification must get authorization from the author.
 */
#include "../testBase.h"
#include <base/core/memory.h>

void PointerTest() {
    auto test = sys::base::core::SharedPtr<int>(new int(85));
    TEST_ASSERT_NOT_NULL(test);
    TEST_ASSERT_EQUAL(85, *test);
    {
        auto test2 = test;
        TEST_ASSERT_EQUAL(2, test.getCount());
        TEST_ASSERT(test2 == test)
        TEST_ASSERT_FALSE(test2 != test)
    }
    TEST_ASSERT_EQUAL(1, test.getCount());
    auto test2 = sys::base::core::SharedPtr<int>(new int(85));
    TEST_ASSERT(*test2 == *test)
    TEST_ASSERT(test2 != test)
}

void PointerCast() {
    struct ObjectA {
        [[nodiscard]] virtual uint8_t id() const { return 28; }
        virtual ~ObjectA() = default;
    };

    struct ObjectB : public ObjectA {
        [[nodiscard]] uint8_t id() const override { return 18; }
        [[nodiscard]] uint8_t id2() const { return id() + 20; }
        ~ObjectB() override = default;
    };
    auto testA = sys::base::core::SharedPtr<ObjectA>(new ObjectB);
    TEST_ASSERT_EQUAL(18, testA->id());
    {
        auto testB = testA.cast<ObjectB>();
        TEST_ASSERT(testB != nullptr)
        //TEST_ASSERT_EQUAL(38, testB->id2());
        //TEST_ASSERT_EQUAL(2, testB.getCount());
    }
    TEST_ASSERT(testA != nullptr)
    TEST_ASSERT_EQUAL(18, testA->id());
}

void runTests() {
    UNITY_BEGIN();
    RUN_TEST(PointerTest);
    RUN_TEST(PointerCast);
    UNITY_END();
}
