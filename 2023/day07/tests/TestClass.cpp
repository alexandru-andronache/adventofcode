#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day07 {
    TEST_F(Tests2023Day07, part_1_test) {
        ASSERT_EQ(part_1("../2023/day07/input_test.in"), 6440);
    }

    TEST_F(Tests2023Day07, part_1_real_test) {
        ASSERT_EQ(part_1("../2023/day07/input.in"), 246163188);
    }

    TEST_F(Tests2023Day07, part_2_test) {
        ASSERT_EQ(part_2("../2023/day07/input_test.in"), 5905);
    }

    TEST_F(Tests2023Day07, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day07/input.in"), 245794069);
    }
}