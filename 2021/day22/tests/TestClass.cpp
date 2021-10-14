#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day22{
    TEST_F(Tests2021Day22, part_1_test) {
        ASSERT_EQ(part_1("../2021/day22/input_test.in"), 0);
    }

    TEST_F(Tests2021Day22, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day22/input.in"), 0);
    }

    TEST_F(Tests2021Day22, part_2_test) {
        ASSERT_EQ(part_2("../2021/day22/input_test.in"), 0);
    }

    TEST_F(Tests2021Day22, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day22/input.in"), 0);
    }
}