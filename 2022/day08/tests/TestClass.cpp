#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day08{
    TEST_F(Tests2022Day08, part_1_test) {
        ASSERT_EQ(part_1("../2022/day08/input_test.in"), 21);
    }

    TEST_F(Tests2022Day08, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day08/input.in"), 1713);
    }

    TEST_F(Tests2022Day08, part_2_test) {
        ASSERT_EQ(part_2("../2022/day08/input_test.in"), 8);
    }

    TEST_F(Tests2022Day08, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day08/input.in"), 268464);
    }
}