#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day16 {
    TEST_F(Tests2022Day16, part_1_test) {
        ASSERT_EQ(part_1("../2022/day16/input_test.in"), 1651);
    }

    TEST_F(Tests2022Day16, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day16/input.in"), 2114);
    }

    TEST_F(Tests2022Day16, part_2_test) {
        ASSERT_EQ(part_2("../2022/day16/input_test.in"), 1707);
    }

    TEST_F(Tests2022Day16, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day16/input.in"), 2666);
    }
}