#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day10{
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2019/day10/input_test.in"), 8);
    }

    TEST_F(TestClass, part_1_test_2) {
        ASSERT_EQ(part_1("../2019/day10/input_test2.in"), 33);
    }

    TEST_F(TestClass, part_1_test_3) {
        ASSERT_EQ(part_1("../2019/day10/input_test3.in"), 210);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day10/input.in"), 214);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2019/day10/input_test3.in"), 802);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day10/input.in"), 502);
    }
}