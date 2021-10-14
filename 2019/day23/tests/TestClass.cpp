#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day23 {
    TEST_F(Tests2019Day23, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day23/input.in"), 24922);
    }

    TEST_F(Tests2019Day23, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day23/input.in"), 19478);
    }
}
