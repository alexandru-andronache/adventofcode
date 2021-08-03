#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day06 {
    TEST_F(Tests2018Day06, part_1_test) {
        ASSERT_EQ(part_1("../2018/day06/input_test.in"), 17);
    }

    TEST_F(Tests2018Day06, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day06/input.in"), 3358);
    }

    TEST_F(Tests2018Day06, part_2_test) {
        ASSERT_EQ(part_2("../2018/day06/input_test.in", 32), 16);
    }

    TEST_F(Tests2018Day06, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day06/input.in"), 45909);
    }
}