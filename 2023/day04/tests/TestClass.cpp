#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day04 {
    TEST_F(Tests2023Day04, part_1_test) {
        ASSERT_EQ(part_1("../2023/day04/input_test.in"), 13);
    }

    TEST_F(Tests2023Day04, part_1_real_test) {
        ASSERT_EQ(part_1("../2023/day04/input.in"), 23441);
    }

    TEST_F(Tests2023Day04, part_2_test) {
        ASSERT_EQ(part_2("../2023/day04/input_test.in"), 30);
    }

    TEST_F(Tests2023Day04, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day04/input.in"), 5923918);
    }
}