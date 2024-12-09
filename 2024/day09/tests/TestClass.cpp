#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day09 {
    TEST_F(Tests2024Day09, part_1_test) {
        ASSERT_EQ(part_1("../2024/day09/input_test.in"), 1928);
    }

    TEST_F(Tests2024Day09, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day09/input.in"), 6323641412437);
    }

    TEST_F(Tests2024Day09, part_2_test) {
        ASSERT_EQ(part_2("../2024/day09/input_test.in"), 2858);
    }

    TEST_F(Tests2024Day09, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day09/input.in"), 6351801932670);
    }
}
