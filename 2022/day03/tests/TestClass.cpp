#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day03 {
    TEST_F(Tests2022Day03, part_1_test) {
        ASSERT_EQ(part_1("../2022/day03/input_test.in"), 157);
    }

    TEST_F(Tests2022Day03, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day03/input.in"), 7597);
    }

    TEST_F(Tests2022Day03, part_2_test) {
        ASSERT_EQ(part_2("../2022/day03/input_test.in"), 70);
    }

    TEST_F(Tests2022Day03, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day03/input.in"), 2607);
    }
}