#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day02 {
    TEST_F(Tests2016Day02, part_1_test) {
        ASSERT_EQ(part_1("../2016/day02/input_test.in"), "1985");
    }

    TEST_F(Tests2016Day02, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day02/input.in"), "61529");
    }

    TEST_F(Tests2016Day02, part_2_test) {
        ASSERT_EQ(part_2("../2016/day02/input_test.in"), "5DB3");
    }

    TEST_F(Tests2016Day02, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day02/input.in"), "C2C28");
    }
}