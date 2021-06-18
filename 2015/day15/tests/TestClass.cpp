#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day15 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2015/day15/input_test.in", 100), 62842880);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day15/input.in", 100), 18965440);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2015/day15/input_test.in", 100, 500), 57600000);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day15/input.in", 100, 500), 15862900);
    }
}