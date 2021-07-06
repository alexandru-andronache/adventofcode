#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day14{
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2019/day14/input_test.in"), 2210736);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day14/input.in"), 198984);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2019/day14/input_test.in"), 460664);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day14/input.in"), 7659732);
    }
}