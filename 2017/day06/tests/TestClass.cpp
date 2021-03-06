#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day06 {
    TEST_F(Tests2017Day06, part_1_test) {
        ASSERT_EQ(part_1("../2017/day06/input_test.in"), 5);
    }

    TEST_F(Tests2017Day06, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day06/input.in"), 5042);
    }

    TEST_F(Tests2017Day06, part_2_test) {
        ASSERT_EQ(part_2("../2017/day06/input_test.in"), 4);
    }

    TEST_F(Tests2017Day06, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day06/input.in"), 1086);
    }
}