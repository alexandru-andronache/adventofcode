#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day14{
    TEST_F(Tests2022Day14, part_1_test) {
        ASSERT_EQ(part_1("../2022/day14/input_test.in"), 24);
    }

    TEST_F(Tests2022Day14, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day14/input.in"), 1199);
    }

    TEST_F(Tests2022Day14, part_2_test) {
        ASSERT_EQ(part_2("../2022/day14/input_test.in"), 93);
    }

    TEST_F(Tests2022Day14, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day14/input.in"), 23925);
    }
}