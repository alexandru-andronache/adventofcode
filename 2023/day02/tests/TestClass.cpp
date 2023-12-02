#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day02 {
    TEST_F(Tests2023Day02, part_1_test) {
        ASSERT_EQ(part_1("../2023/day02/input_test.in"), 8);
    }

    TEST_F(Tests2023Day02, part_1_real_test) {
        ASSERT_EQ(part_1("../2023/day02/input.in"), 2369);
    }

    TEST_F(Tests2023Day02, part_2_test) {
        ASSERT_EQ(part_2("../2023/day02/input_test.in"), 2286);
    }

    TEST_F(Tests2023Day02, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day02/input.in"), 66363);
    }
}