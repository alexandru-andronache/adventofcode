#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day13 {
    TEST_F(Tests2022Day13, part_1_test) {
        ASSERT_EQ(part_1("../2022/day13/input_test.in"), 0);
    }

    TEST_F(Tests2022Day13, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day13/input.in"), 0);
    }

    TEST_F(Tests2022Day13, part_2_test) {
        ASSERT_EQ(part_2("../2022/day13/input_test.in"), 0);
    }

    TEST_F(Tests2022Day13, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day13/input.in"), 0);
    }
}
