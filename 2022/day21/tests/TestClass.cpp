#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day21 {
    TEST_F(Tests2022Day21, part_1_test) {
        ASSERT_EQ(part_1("../2022/day21/input_test.in"), 152);
    }

    TEST_F(Tests2022Day21, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day21/input.in"), 87457751482938);
    }

    TEST_F(Tests2022Day21, part_2_test) {
        ASSERT_EQ(part_2("../2022/day21/input_test.in"), 301);
    }

    TEST_F(Tests2022Day21, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day21/input.in"), 3221245824363);
    }
}