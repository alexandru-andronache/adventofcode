#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day04 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1(), 2814);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2(), 1991);
    }
}