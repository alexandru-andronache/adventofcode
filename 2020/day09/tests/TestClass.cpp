#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day09 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2020/day09/input_test.in", 5), 127);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day09/input.in"), 27911108);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2020/day09/input_test.in", 127), 62);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day09/input.in"), 4023754);
    }
}
