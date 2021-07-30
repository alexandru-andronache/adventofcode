#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day19 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2017/day19/input_test.in"), "ABCDEF");
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day19/input.in"), "SXWAIBUZY");
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2017/day19/input_test.in"), 38);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day19/input.in"), 16676);
    }
}