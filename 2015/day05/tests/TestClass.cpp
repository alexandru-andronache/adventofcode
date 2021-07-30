#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day05 {
    TEST_F(Tests2015Day05, part_1_test) {
        ASSERT_EQ(part_1("../2015/day05/input_test.in"), 2);
    }

    TEST_F(Tests2015Day05, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day05/input.in"), 236);
    }

    TEST_F(Tests2015Day05, part_2_test) {
        ASSERT_EQ(part_2("../2015/day05/input_test2.in"), 2);
    }

    TEST_F(Tests2015Day05, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day05/input.in"), 51);
    }
}