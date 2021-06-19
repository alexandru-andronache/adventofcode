#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day07 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2016/day07/input_test.in"), 2);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day07/input.in"), 110);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2016/day07/input_test2.in"), 3);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day07/input.in"), 242);
    }
}