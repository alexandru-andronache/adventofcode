#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day17{
    TEST_F(Tests2021Day17, part_1_test) {
        ASSERT_EQ(part_1("../2021/day17/input_test.in"), 45);
    }

    TEST_F(Tests2021Day17, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day17/input.in"), 8646);
    }

    TEST_F(Tests2021Day17, part_2_test) {
        ASSERT_EQ(part_2("../2021/day17/input_test.in"), 112);
    }

    TEST_F(Tests2021Day17, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day17/input.in"), 5945);
    }
}