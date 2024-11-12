#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day14{
    TEST_F(Tests2024Day14, part_1_test) {
        ASSERT_EQ(part_1("../2024/day14/input_test.in"), 0);
    }

    TEST_F(Tests2024Day14, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day14/input.in"), 0);
    }

    TEST_F(Tests2024Day14, part_2_test) {
        ASSERT_EQ(part_2("../2024/day14/input_test.in"), 0);
    }

    TEST_F(Tests2024Day14, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day14/input.in"), 0);
    }
}