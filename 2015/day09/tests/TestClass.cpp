#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day09 {
    TEST_F(Tests2015Day09, part_1_test) {
        ASSERT_EQ(part_1("../2015/day09/input_test.in", 3), 605);
    }

    TEST_F(Tests2015Day09, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day09/input.in"), 251);
    }

    TEST_F(Tests2015Day09, part_2_test) {
        ASSERT_EQ(part_2("../2015/day09/input_test.in", 3), 982);
    }

    TEST_F(Tests2015Day09, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day09/input.in"), 898);
    }
}
