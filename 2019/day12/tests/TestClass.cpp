#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day12 {
    TEST_F(Tests2019Day12, part_1_test) {
        ASSERT_EQ(part_1({{-1, 0, 2}, {2, -10, -7}, {4, -8, 8}, {3, 5, -1}}, 10), 179);
    }

    TEST_F(Tests2019Day12, part_1_test_2) {
        ASSERT_EQ(part_1({{-8, -10, 0}, {5, 5, 10}, {2, -7, 3}, {9, -8, -3}}, 100), 1940);
    }

    TEST_F(Tests2019Day12, part_1_real_test) {
        ASSERT_EQ(part_1({{5, -1, 5}, {0, -14, 2}, {16, 4, 0}, {18, 1, 16}}), 7928);
    }

    TEST_F(Tests2019Day12, part_2_test) {
        ASSERT_EQ(part_2({{-8, -10, 0}, {5, 5, 10}, {2, -7, 3}, {9, -8, -3}}), 4686774924);
    }

    TEST_F(Tests2019Day12, part_2_real_test) {
        ASSERT_EQ(part_2({{5, -1, 5}, {0, -14, 2}, {16, 4, 0}, {18, 1, 16}}), 518311327635164);
    }
}