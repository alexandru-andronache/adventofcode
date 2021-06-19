#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day06 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2016/day06/input_test.in"), "easter");
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day06/input.in"), "tzstqsua");
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2016/day06/input_test.in"), "advent");
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day06/input.in"), "myregdnr");
    }
}