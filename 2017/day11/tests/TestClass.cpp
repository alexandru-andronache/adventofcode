#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day11 {
    TEST_F(Tests2017Day11, part_1_test) {
        ASSERT_EQ(part_1("../2017/day11/input_test.in"), 3);
    }

    TEST_F(Tests2017Day11, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day11/input.in"), 808);
    }

    TEST_F(Tests2017Day11, part_2_test) {
        ASSERT_EQ(part_2("../2017/day11/input_test.in"), 3);
    }

    TEST_F(Tests2017Day11, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day11/input.in"), 1556);
    }
}