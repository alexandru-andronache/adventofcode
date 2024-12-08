#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day08{
    TEST_F(Tests2024Day08, part_1_test) {
        ASSERT_EQ(part_1("../2024/day08/input_test.in"), 14);
    }

    TEST_F(Tests2024Day08, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day08/input.in"), 392);
    }

    TEST_F(Tests2024Day08, part_2_test) {
        ASSERT_EQ(part_2("../2024/day08/input_test.in"), 34);
    }

    TEST_F(Tests2024Day08, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day08/input.in"), 1235);
    }
}