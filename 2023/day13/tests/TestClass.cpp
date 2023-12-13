#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day13 {
    TEST_F(Tests2023Day13, part_1_test) {
        ASSERT_EQ(part_1("../2023/day13/input_test.in"), 405);
    }

    TEST_F(Tests2023Day13, part_1_real_test) {
        ASSERT_EQ(part_1("../2023/day13/input.in"), 36041);
    }

    TEST_F(Tests2023Day13, part_2_test) {
        ASSERT_EQ(part_2("../2023/day13/input_test.in"), 400);
    }

    TEST_F(Tests2023Day13, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day13/input.in"), 35915);
    }
}
