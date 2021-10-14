#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day18 {
    TEST_F(Tests2019Day18, part_1_test) {
        ASSERT_EQ(part_1("../2019/day18/input_test.in"), 136);
    }

    TEST_F(Tests2019Day18, part_1_test_2) {
        ASSERT_EQ(part_1("../2019/day18/input_test2.in"), 81);
    }

    TEST_F(Tests2019Day18, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day18/input.in"), 5450);
    }

    TEST_F(Tests2019Day18, part_2_test) {
        ASSERT_EQ(part_2("../2019/day18/input_test3.in"), 72);
    }

    TEST_F(Tests2019Day18, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day18/input.in"), 2020);
    }
}