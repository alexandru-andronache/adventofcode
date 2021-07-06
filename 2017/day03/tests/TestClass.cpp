#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day03 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1(23), 2);
    }

    TEST_F(TestClass, part_1_test_2) {
        ASSERT_EQ(part_1(1024), 31);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1(), 480);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2(), 349975);
    }
}