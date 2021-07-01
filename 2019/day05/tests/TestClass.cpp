#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day05 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day05/input.in"), 7259358);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day05/input.in"), 11826654);
    }
}