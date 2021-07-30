#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day23 {
    TEST_F(Tests2017Day23, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day23/input.in"), 6241);
    }

    TEST_F(Tests2017Day23, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day23/input.in"), 909);
    }
}
