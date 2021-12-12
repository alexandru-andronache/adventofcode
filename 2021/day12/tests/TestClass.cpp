#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day12 {
    TEST_F(Tests2021Day12, part_1_test) {
        ASSERT_EQ(part_1("../2021/day12/input_test.in"), 10);
    }

    TEST_F(Tests2021Day12, part_1_test_2) {
        ASSERT_EQ(part_1("../2021/day12/input_test2.in"), 19);
    }

    TEST_F(Tests2021Day12, part_1_test_3) {
        ASSERT_EQ(part_1("../2021/day12/input_test3.in"), 226);
    }

    TEST_F(Tests2021Day12, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day12/input.in"), 3497);
    }

    TEST_F(Tests2021Day12, part_2_test) {
        ASSERT_EQ(part_2("../2021/day12/input_test.in"), 36);
    }

    TEST_F(Tests2021Day12, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day12/input.in"), 93686);
    }
}