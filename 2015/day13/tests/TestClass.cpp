#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day13 {
    TEST_F(Tests2015Day13, part_1_test) {
        ASSERT_EQ(part_1("../2015/day13/input_test.in"), 330);
    }

    TEST_F(Tests2015Day13, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day13/input.in"), 733);
    }

    TEST_F(Tests2015Day13, part_2_test) {
        ASSERT_EQ(part_2("../2015/day13/input_test.in"), 286);
    }

    TEST_F(Tests2015Day13, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day13/input.in"), 725);
    }
}
