#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day11 {
    TEST_F(Tests2023Day11, part_1_test) {
        ASSERT_EQ(part_1("../2023/day11/input_test.in"), 374);
    }

    TEST_F(Tests2023Day11, part_1_real_test) {
        ASSERT_EQ(part_1("../2023/day11/input.in"), 9681886);
    }

    TEST_F(Tests2023Day11, part_2_test) {
        ASSERT_EQ(part_2("../2023/day11/input_test.in", 10), 1030);
    }

    TEST_F(Tests2023Day11, part_2_test_2) {
        ASSERT_EQ(part_2("../2023/day11/input_test.in", 100), 8410);
    }

    TEST_F(Tests2023Day11, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day11/input.in", 1000000), 791134099634);
    }
}