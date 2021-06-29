#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day24 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2019/day24/input_test.in"), 2129920);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day24/input.in"), 18401265);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2019/day24/input_test.in", 10), 99);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day24/input.in"), 2078);
    }
}