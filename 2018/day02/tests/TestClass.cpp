#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day02 {
    TEST_F(Tests2018Day02, part_1_test) {
        ASSERT_EQ(part_1("../2018/day02/input_test.in"), 12);
    }

    TEST_F(Tests2018Day02, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day02/input.in"), 5166);
    }

    TEST_F(Tests2018Day02, part_2_test) {
        ASSERT_EQ(part_2("../2018/day02/input_test2.in"), "fgij");
    }

    TEST_F(Tests2018Day02, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day02/input.in"), "cypueihajytordkgzxfqplbwn");
    }
}