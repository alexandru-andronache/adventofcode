#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day24 {
    TEST_F(Tests2017Day24, part_1_test) {
        ASSERT_EQ(part_1("../2017/day24/input_test.in"), 31);
    }

    TEST_F(Tests2017Day24, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day24/input.in"), 1868);
    }

    TEST_F(Tests2017Day24, part_2_test) {
        ASSERT_EQ(part_2("../2017/day24/input_test.in"), 19);
    }

    TEST_F(Tests2017Day24, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day24/input.in"), 1841);
    }
}