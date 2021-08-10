#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day19 {
    TEST_F(Tests2018Day19, part_1_test) {
        ASSERT_EQ(part_1("../2018/day19/input_test.in"), 6);
    }

    TEST_F(Tests2018Day19, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day19/input.in"), 2160);
    }

    TEST_F(Tests2018Day19, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day19/input.in"), 25945920);
    }
}