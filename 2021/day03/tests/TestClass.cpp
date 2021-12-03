#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day03 {
    TEST_F(Tests2021Day03, part_1_test) {
        ASSERT_EQ(part_1("../2021/day03/input_test.in"), 198);
    }

    TEST_F(Tests2021Day03, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day03/input.in"), 4006064);
    }

    TEST_F(Tests2021Day03, part_2_test) {
        ASSERT_EQ(part_2("../2021/day03/input_test.in"), 230);
    }

    TEST_F(Tests2021Day03, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day03/input.in"), 5941884);
    }
}