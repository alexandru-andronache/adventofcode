#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day10{
    TEST_F(Tests2016Day10, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day10/input.in"), 161);
    }

    TEST_F(Tests2016Day10, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day10/input.in"), 133163);
    }
}