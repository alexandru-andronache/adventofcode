#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day23 {
    TEST_F(Tests2016Day23, part_1_test) {
        ASSERT_EQ(part_1("../2016/day23/input_test.in"), 3);
    }

    TEST_F(Tests2016Day23, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day23/input.in"), 10661);
    }

    TEST_F(Tests2016Day23, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day23/input.in"), 479007221);
    }
}
