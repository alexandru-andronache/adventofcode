#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day13 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day13/input.in"), 306);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day13/input.in"), 15328);
    }
}
