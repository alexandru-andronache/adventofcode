#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day10{
    TEST_F(Tests2018Day10, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day10/input.in"), "CRXKEZPZ");
    }

    TEST_F(Tests2018Day10, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day10/input.in"), 10081);
    }
}