#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day25 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2019/day25/input_test.in"), 0);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day25/input.in"), 0);
    }
}
