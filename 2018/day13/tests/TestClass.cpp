#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day13 {
    TEST_F(Tests2018Day13, part_1_test) {
        auto sol = part_1("../2018/day13/input_test.in");
        ASSERT_EQ(sol.first, 7);
        ASSERT_EQ(sol.second, 3);
    }

    TEST_F(Tests2018Day13, part_1_real_test) {
        auto sol = part_1("../2018/day13/input.in");
        ASSERT_EQ(sol.first, 103);
        ASSERT_EQ(sol.second, 85);
    }

    TEST_F(Tests2018Day13, part_2_test) {
        auto sol = part_2("../2018/day13/input_test2.in");
        ASSERT_EQ(sol.first, 6);
        ASSERT_EQ(sol.second, 4);
    }

    TEST_F(Tests2018Day13, part_2_real_test) {
        auto sol = part_2("../2018/day13/input.in");
        ASSERT_EQ(sol.first, 88);
        ASSERT_EQ(sol.second, 64);
    }
}
