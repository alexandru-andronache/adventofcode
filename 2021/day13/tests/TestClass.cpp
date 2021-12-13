#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day13 {
    TEST_F(Tests2021Day13, part_1_test) {
        ASSERT_EQ(part_1("../2021/day13/input_test.in"), 17);
    }

    TEST_F(Tests2021Day13, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day13/input.in"), 638);
    }

    TEST_F(Tests2021Day13, part_2_test) {
        ASSERT_EQ(part_2("../2021/day13/input_test.in"), 16);
    }

    TEST_F(Tests2021Day13, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day13/input.in"), 99);
    }
}
