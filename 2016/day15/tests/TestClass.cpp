#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day15 {
    TEST_F(Tests2016Day15, part_1_test) {
        ASSERT_EQ(part_1("../2016/day15/input_test.in"), 5);
    }

    TEST_F(Tests2016Day15, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day15/input.in"), 317371);
    }

    TEST_F(Tests2016Day15, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day15/input.in"), 2080951);
    }
}