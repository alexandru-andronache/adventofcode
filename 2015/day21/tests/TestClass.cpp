#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day21 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1(100, 8, 2, 100), 91);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2(100, 8, 2, 100), 158);
    }
}