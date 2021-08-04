#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day09 {
    TEST_F(Tests2018Day09, part_1_test) {
        ASSERT_EQ(part_1(10, 1618), 8317);
    }

    TEST_F(Tests2018Day09, part_1_test_2) {
        ASSERT_EQ(part_1(13, 7999), 146373);
    }

    TEST_F(Tests2018Day09, part_1_test_3) {
        ASSERT_EQ(part_1(17, 1104), 2764);
    }

    TEST_F(Tests2018Day09, part_1_test_4) {
        ASSERT_EQ(part_1(21, 6111), 54718);
    }

    TEST_F(Tests2018Day09, part_1_test_5) {
        ASSERT_EQ(part_1(30, 5807), 37305);
    }

    TEST_F(Tests2018Day09, part_1_real_test) {
        ASSERT_EQ(part_1(438, 71626), 398730);
    }

    TEST_F(Tests2018Day09, part_2_real_test) {
        ASSERT_EQ(part_2(438, 71626), 3349635509);
    }
}
