#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day17{
    TEST_F(Tests2019Day17, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day17/input.in"), 3920);
    }

    TEST_F(Tests2019Day17, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day17/input.in"), 673996);
    }
}