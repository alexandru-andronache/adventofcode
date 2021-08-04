#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day11 {
    TEST_F(Tests2018Day11, part_1_test) {
        auto sol = part_1(18, 300);
        ASSERT_EQ(sol.first, 33);
        ASSERT_EQ(sol.second, 45);
    }

    TEST_F(Tests2018Day11, part_1_test_2) {
        auto sol = part_1(42, 300);
        ASSERT_EQ(sol.first, 21);
        ASSERT_EQ(sol.second, 61);
    }

    TEST_F(Tests2018Day11, part_1_real_test) {
        auto sol = part_1(1788, 300);
        ASSERT_EQ(sol.first, 235);
        ASSERT_EQ(sol.second, 35);
    }

    TEST_F(Tests2018Day11, part_2_test) {
        auto [x, y, s] = part_2(18, 300);
        ASSERT_EQ(x, 90);
        ASSERT_EQ(y, 269);
        ASSERT_EQ(s, 16);
    }

    TEST_F(Tests2018Day11, part_2_test_2) {
        auto [x, y, s] = part_2(42, 300);
        ASSERT_EQ(x, 232);
        ASSERT_EQ(y, 251);
        ASSERT_EQ(s, 12);
    }

    TEST_F(Tests2018Day11, part_2_real_test) {
        auto [x, y, s] = part_2(1788, 300);
        ASSERT_EQ(x, 142);
        ASSERT_EQ(y, 265);
        ASSERT_EQ(s, 7);
    }
}