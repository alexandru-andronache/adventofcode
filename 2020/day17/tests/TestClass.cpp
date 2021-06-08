#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day17{
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2020/day17/input_test.in"), 112);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2020/day17/input_test.in"), 848);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day17/input.in"), 273);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day17/input.in"), 1504);
    }
}