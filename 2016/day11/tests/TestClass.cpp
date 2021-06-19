#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day11 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1(), 31);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2(), 55);
    }
}