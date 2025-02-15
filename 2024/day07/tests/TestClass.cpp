#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day07 {
    TEST_F(Tests2024Day07, part_1_test) {
        ASSERT_EQ(part_1("../2024/day07/input_test.in"), 3749);
    }

    TEST_F(Tests2024Day07, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day07/input.in"), 5837374519342);
    }

    TEST_F(Tests2024Day07, part_2_test) {
        ASSERT_EQ(part_2("../2024/day07/input_test.in"), 11387);
    }

    TEST_F(Tests2024Day07, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day07/input.in"), 492383931650959);
    }
}