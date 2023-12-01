#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day01 {
    TEST_F(Tests2023Day01, part_1_test) {
        ASSERT_EQ(part_1("../2023/day01/input_test.in"), 142);
    }

    TEST_F(Tests2023Day01, part_1_real_test) {
        ASSERT_EQ(part_1("../2023/day01/input.in"), 55834);
    }

    TEST_F(Tests2023Day01, part_2_test) {
        ASSERT_EQ(part_2("../2023/day01/input_test2.in"), 281);
    }

    TEST_F(Tests2023Day01, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day01/input.in"), 53221);
    }
}