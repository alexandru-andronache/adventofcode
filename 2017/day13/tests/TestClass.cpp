#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day13 {
    TEST_F(Tests2017Day13, part_1_test) {
        ASSERT_EQ(part_1("../2017/day13/input_test.in"), 24);
    }

    TEST_F(Tests2017Day13, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day13/input.in"), 2384);
    }

    TEST_F(Tests2017Day13, part_2_test) {
        ASSERT_EQ(part_2("../2017/day13/input_test.in"), 10);
    }

    TEST_F(Tests2017Day13, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day13/input.in"), 3921270);
    }
}
