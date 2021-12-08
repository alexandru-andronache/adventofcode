#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day08{
    TEST_F(Tests2021Day08, part_1_test) {
        ASSERT_EQ(part_1("../2021/day08/input_test.in"), 26);
    }

    TEST_F(Tests2021Day08, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day08/input.in"), 449);
    }

    TEST_F(Tests2021Day08, part_2_test) {
        ASSERT_EQ(part_2("../2021/day08/input_test.in"), 61229);
    }

    TEST_F(Tests2021Day08, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day08/input.in"), 968175);
    }
}