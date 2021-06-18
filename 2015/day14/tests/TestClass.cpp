#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day14{
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2015/day14/input_test.in", 1000), 1120);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day14/input.in", 2503), 2660);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2015/day14/input_test.in", 1000), 689);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day14/input.in", 2503), 1256);
    }
}