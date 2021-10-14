#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day11 {
    TEST_F(Tests2020Day11, part_1_test) {
        ASSERT_EQ(part_1("../2020/day11/input_test.in"), 37);
    }

    TEST_F(Tests2020Day11, part_2_test) {
        ASSERT_EQ(part_2("../2020/day11/input_test.in"), 26);
    }

    TEST_F(Tests2020Day11, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day11/input.in"), 2483);
    }

    TEST_F(Tests2020Day11, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day11/input.in"), 2285);
    }
}