#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day07 {
    TEST_F(Tests2015Day07, part_1_test) {
        ASSERT_EQ(part_1("../2015/day07/input_test.in", "i"), 65079);
    }

    TEST_F(Tests2015Day07, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day07/input.in"), 956);
    }

    TEST_F(Tests2015Day07, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day07/input.in", 956), 40149);
    }
}