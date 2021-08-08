#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day17{
    TEST_F(Tests2018Day17, part_1_test) {
        ASSERT_EQ(part_1("../2018/day17/input_test.in"), 57);
    }

    TEST_F(Tests2018Day17, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day17/input.in"), 52800);
    }

    TEST_F(Tests2018Day17, part_2_test) {
        ASSERT_EQ(part_2("../2018/day17/input_test.in"), 29);
    }

    TEST_F(Tests2018Day17, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day17/input.in"), 45210);
    }
}