#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day12 {
    TEST_F(Tests2018Day12, part_1_test) {
        ASSERT_EQ(part_1("../2018/day12/input_test.in"), 325);
    }

    TEST_F(Tests2018Day12, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day12/input.in"), 3230);
    }

    TEST_F(Tests2018Day12, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day12/input.in"), 4400000000304);
    }
}