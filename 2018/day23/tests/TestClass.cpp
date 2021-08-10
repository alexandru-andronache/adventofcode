#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day23 {
    TEST_F(Tests2018Day23, part_1_test) {
        ASSERT_EQ(part_1("../2018/day23/input_test.in"), 7);
    }

    TEST_F(Tests2018Day23, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day23/input.in"), 341);
    }

    TEST_F(Tests2018Day23, part_2_test) {
        ASSERT_EQ(part_2("../2018/day23/input_test2.in"), 36);
    }

    TEST_F(Tests2018Day23, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day23/input.in"), 105191907);
    }
}
