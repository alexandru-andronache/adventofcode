#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day08{
    TEST_F(Tests2023Day08, part_1_test) {
        ASSERT_EQ(part_1("../2023/day08/input_test.in"), 6);
    }

    TEST_F(Tests2023Day08, part_1_real_test) {
        ASSERT_EQ(part_1("../2023/day08/input.in"), 22357);
    }

    TEST_F(Tests2023Day08, part_2_test) {
        ASSERT_EQ(part_2("../2023/day08/input_test2.in"), 6);
    }

    TEST_F(Tests2023Day08, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day08/input.in"), 10371555451871);
    }
}