#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day07 {
    TEST_F(Tests2022Day07, part_1_test) {
        ASSERT_EQ(part_1("../2022/day07/input_test.in"), 0);
    }

    TEST_F(Tests2022Day07, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day07/input.in"), 0);
    }

    TEST_F(Tests2022Day07, part_2_test) {
        ASSERT_EQ(part_2("../2022/day07/input_test.in"), 0);
    }

    TEST_F(Tests2022Day07, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day07/input.in"), 0);
    }
}