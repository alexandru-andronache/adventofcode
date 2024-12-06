#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day06 {
    TEST_F(Tests2024Day06, part_1_test) {
        ASSERT_EQ(part_1("../2024/day06/input_test.in"), 41);
    }

    TEST_F(Tests2024Day06, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day06/input.in"), 4752);
    }

    TEST_F(Tests2024Day06, part_2_test) {
        ASSERT_EQ(part_2("../2024/day06/input_test.in"), 6);
    }

    TEST_F(Tests2024Day06, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day06/input.in"), 1719);
    }
}