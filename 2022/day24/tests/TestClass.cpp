#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day24 {
    TEST_F(Tests2022Day24, part_1_test) {
        ASSERT_EQ(part_1("../2022/day24/input_test.in"), 18);
    }

    TEST_F(Tests2022Day24, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day24/input.in"), 242);
    }

    TEST_F(Tests2022Day24, part_2_test) {
        ASSERT_EQ(part_2("../2022/day24/input_test.in"), 54);
    }

    TEST_F(Tests2022Day24, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day24/input.in"), 720);
    }
}