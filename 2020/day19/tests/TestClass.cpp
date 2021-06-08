#include "TestClass.h"

namespace aoc2020_day19 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2020/day19/input_test.in"), 2);
    }

    TEST_F(TestClass, part_1_large_test) {
        ASSERT_EQ(part_1("../2020/day19/input_test2.in"), 3);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day19/input.in"), 220);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2020/day19/input_test2.in"), 12);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day19/input.in"), 439);
    }
}