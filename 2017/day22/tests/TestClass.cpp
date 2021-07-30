#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day22{
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2017/day22/input_test.in"), 5587);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day22/input.in"), 5538);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2017/day22/input_test.in"), 2511944);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day22/input.in"), 2511090);
    }
}