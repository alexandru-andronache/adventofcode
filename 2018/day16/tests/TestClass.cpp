#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day16 {
    TEST_F(Tests2018Day16, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day16/input.in"), 529);
    }

    TEST_F(Tests2018Day16, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day16/input.in"), 573);
    }
}