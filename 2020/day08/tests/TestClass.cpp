#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day08{
    TEST_F(Tests2020Day08, part_1_test) {
        ASSERT_EQ(part_1("../2020/day08/input_test.in"), 5);
    }

    TEST_F(Tests2020Day08, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day08/input.in"), 1766);
    }

    TEST_F(Tests2020Day08, part_2_test) {
        ASSERT_EQ(part_2("../2020/day08/input_test.in"), 8);
    }

    TEST_F(Tests2020Day08, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day08/input.in"), 1639);
    }
}