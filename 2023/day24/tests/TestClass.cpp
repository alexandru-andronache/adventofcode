#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day24 {
    TEST_F(Tests2023Day24, part_1_test) {
        ASSERT_EQ(part_1("../2023/day24/input_test.in"), 0);
    }

    TEST_F(Tests2023Day24, part_1_real_test) {
        ASSERT_EQ(part_1("../2023/day24/input.in"), 0);
    }

    TEST_F(Tests2023Day24, part_2_test) {
        ASSERT_EQ(part_2("../2023/day24/input_test.in"), 0);
    }

    TEST_F(Tests2023Day24, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day24/input.in"), 0);
    }
}