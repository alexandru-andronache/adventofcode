#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day09 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2017/day09/input_test.in"), 3);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day09/input.in"), 14204);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2017/day09/input_test2.in"), 10);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day09/input.in"), 6622);
    }
}
