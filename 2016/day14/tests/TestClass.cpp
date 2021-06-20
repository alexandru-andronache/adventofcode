#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day14{
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("abc"), 22728);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("cuanljph"), 23769);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("cuanljph"), 20606);
    }
}