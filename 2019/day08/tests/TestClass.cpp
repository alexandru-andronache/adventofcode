#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day08{
    TEST_F(Tests2019Day08, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day08/input.in"), 1905);
    }
}