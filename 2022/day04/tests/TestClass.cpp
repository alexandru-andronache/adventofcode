#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day04 {
    TEST_F(Tests2022Day04, part_1_test) {
        ASSERT_EQ(part_1("../2022/day04/input_test.in"), 2);
    }

    TEST_F(Tests2022Day04, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day04/input.in"), 580);
    }

    TEST_F(Tests2022Day04, part_2_test) {
        ASSERT_EQ(part_2("../2022/day04/input_test.in"), 4);
    }

    TEST_F(Tests2022Day04, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day04/input.in"), 895);
    }
}