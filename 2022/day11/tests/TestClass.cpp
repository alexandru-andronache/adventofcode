#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day11 {
    TEST_F(Tests2022Day11, part_1_test) {
        ASSERT_EQ(part_1("../2022/day11/input_test.in"), 10605);
    }

    TEST_F(Tests2022Day11, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day11/input.in"), 51075);
    }

    TEST_F(Tests2022Day11, part_2_test) {
        ASSERT_EQ(part_2("../2022/day11/input_test.in"), 2713310158);
    }

    TEST_F(Tests2022Day11, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day11/input.in"), 11741456163);
    }
}