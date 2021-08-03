#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day14{
    TEST_F(Tests2018Day14, part_1_test) {
        ASSERT_EQ(part_1("../2018/day14/input_test.in"), 0);
    }

    TEST_F(Tests2018Day14, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day14/input.in"), 0);
    }

    TEST_F(Tests2018Day14, part_2_test) {
        ASSERT_EQ(part_2("../2018/day14/input_test.in"), 0);
    }

    TEST_F(Tests2018Day14, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day14/input.in"), 0);
    }
}