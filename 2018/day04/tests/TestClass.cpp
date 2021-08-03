#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day04 {
    TEST_F(Tests2018Day04, part_1_test) {
        ASSERT_EQ(part_1("../2018/day04/input_test.in"), 240);
    }

    TEST_F(Tests2018Day04, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day04/input.in"), 94040);
    }

    TEST_F(Tests2018Day04, part_2_test) {
        ASSERT_EQ(part_2("../2018/day04/input_test.in"), 4455);
    }

    TEST_F(Tests2018Day04, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day04/input.in"), 39940);
    }
}