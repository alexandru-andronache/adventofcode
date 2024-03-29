#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day17{
    TEST_F(Tests2022Day17, part_1_test) {
        ASSERT_EQ(part_1("../2022/day17/input_test.in"), 3068);
    }

    TEST_F(Tests2022Day17, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day17/input.in"), 3092);
    }

    TEST_F(Tests2022Day17, part_2_test) {
        ASSERT_EQ(part_2("../2022/day17/input_test.in"), 0);
    }

    TEST_F(Tests2022Day17, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day17/input.in"), 0);
    }
}