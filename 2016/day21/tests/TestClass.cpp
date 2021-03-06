#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day21 {
    TEST_F(Tests2016Day21, part_1_test) {
        ASSERT_EQ(part_1("../2016/day21/input_test.in", "abcde"), "decab");
    }

    TEST_F(Tests2016Day21, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day21/input.in", "abcdefgh"), "bgfacdeh");
    }

    TEST_F(Tests2016Day21, part_2_test) {
        ASSERT_EQ(part_2("../2016/day21/input_test.in", "decab"), "deabc");
    }

    TEST_F(Tests2016Day21, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day21/input.in", "fbgdceah"), "bdgheacf");
    }
}