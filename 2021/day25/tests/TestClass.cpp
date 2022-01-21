#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day25 {
    TEST_F(Tests2021Day25, part_1_test) {
        ASSERT_EQ(part_1("../2021/day25/input_test.in"), 58);
    }

    TEST_F(Tests2021Day25, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day25/input.in"), 489);
    }
}
