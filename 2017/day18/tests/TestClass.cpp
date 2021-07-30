#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day18 {
    TEST_F(Tests2017Day18, part_1_test) {
        ASSERT_EQ(part_1("../2017/day18/input_test.in"), 4);
    }

    TEST_F(Tests2017Day18, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day18/input.in"), 3423);
    }

    TEST_F(Tests2017Day18, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day18/input.in"), 7493);
    }
}