#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day11 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day11/input.in"), 2016);
    }
}