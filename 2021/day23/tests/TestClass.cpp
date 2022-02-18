#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day23 {
    TEST_F(Tests2021Day23, part_1_test) {
        ASSERT_EQ(part_1("../2021/day23/input_test.in"), 12521);
    }

    TEST_F(Tests2021Day23, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day23/input.in"), 13495);
    }

    TEST_F(Tests2021Day23, part_2_test) {
        ASSERT_EQ(part_2("../2021/day23/input_test.in"), 44169);
    }

    TEST_F(Tests2021Day23, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day23/input.in"), 53767);
    }
}
