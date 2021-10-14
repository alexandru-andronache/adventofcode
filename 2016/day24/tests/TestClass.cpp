#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day24 {
    TEST_F(Tests2016Day24, part_1_test) {
        ASSERT_EQ(part_1("../2016/day24/input_test.in"), 14);
    }

    TEST_F(Tests2016Day24, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day24/input.in"), 442);
    }

    TEST_F(Tests2016Day24, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day24/input.in"), 660);
    }
}