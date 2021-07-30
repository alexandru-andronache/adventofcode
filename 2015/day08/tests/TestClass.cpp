#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day08{
    TEST_F(Tests2015Day08, part_1_test) {
        ASSERT_EQ(part_1("../2015/day08/input_test.in"), 12);
    }

    TEST_F(Tests2015Day08, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day08/input.in"), 1342);
    }

    TEST_F(Tests2015Day08, part_2_test) {
        ASSERT_EQ(part_2("../2015/day08/input_test.in"), 19);
    }

    TEST_F(Tests2015Day08, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day08/input.in"), 2074);
    }
}