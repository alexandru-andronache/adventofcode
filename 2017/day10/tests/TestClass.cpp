#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day10{
    TEST_F(Tests2017Day10, part_1_test) {
        ASSERT_EQ(part_1("../2017/day10/input_test.in", 5), 12);
    }

    TEST_F(Tests2017Day10, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day10/input.in"), 3770);
    }

    TEST_F(Tests2017Day10, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day10/input.in"), "a9d0e68649d0174c8756a59ba21d4dc6");
    }
}