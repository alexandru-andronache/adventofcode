#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day06 {
    TEST_F(Tests2019Day06, part_1_test) {
        ASSERT_EQ(part_1("../2019/day06/input_test.in"), 42);
    }

    TEST_F(Tests2019Day06, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day06/input.in"), 186597);
    }

    TEST_F(Tests2019Day06, part_2_test) {
        ASSERT_EQ(part_2("../2019/day06/input_test2.in"), 4);
    }

    TEST_F(Tests2019Day06, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day06/input.in"), 412);
    }
}