#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day12 {
    TEST_F(Tests2016Day12, part_1_test) {
        ASSERT_EQ(part_1("../2016/day12/input_test.in"), 42);
    }

    TEST_F(Tests2016Day12, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day12/input.in"), 318077);
    }

    TEST_F(Tests2016Day12, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day12/input.in"), 9227731);
    }
}