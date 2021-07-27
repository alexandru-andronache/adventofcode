#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day12 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2017/day12/input_test.in"), 6);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day12/input.in"), 145);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2017/day12/input_test.in"), 2);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day12/input.in"), 207);
    }
}