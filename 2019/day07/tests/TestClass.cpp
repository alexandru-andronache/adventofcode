#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day07 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2019/day07/input_test.in"), 0);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day07/input.in"), 0);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2019/day07/input_test.in"), 0);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day07/input.in"), 0);
    }
}