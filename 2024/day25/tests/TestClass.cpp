#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day25 {
    TEST_F(Tests2024Day25, part_1_test) {
        ASSERT_EQ(part_1("../2024/day25/input_test.in"), 0);
    }

    TEST_F(Tests2024Day25, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day25/input.in"), 0);
    }
}
