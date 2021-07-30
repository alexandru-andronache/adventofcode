#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day24 {
    TEST_F(Tests2015Day24, part_1_test) {
        ASSERT_EQ(part_1("../2015/day24/input_test.in"), 99);
    }

    TEST_F(Tests2015Day24, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day24/input.in"), 10723906903);
    }

    TEST_F(Tests2015Day24, part_2_test) {
        ASSERT_EQ(part_2("../2015/day24/input_test.in"), 44);
    }

    TEST_F(Tests2015Day24, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day24/input.in"), 74850409);
    }
}