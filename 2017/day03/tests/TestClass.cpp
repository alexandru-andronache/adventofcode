#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day03 {
    TEST_F(Tests2017Day03, part_1_test) {
        ASSERT_EQ(part_1(23), 2);
    }

    TEST_F(Tests2017Day03, part_1_test_2) {
        ASSERT_EQ(part_1(1024), 31);
    }

    TEST_F(Tests2017Day03, part_1_real_test) {
        ASSERT_EQ(part_1(), 480);
    }

    TEST_F(Tests2017Day03, part_2_real_test) {
        ASSERT_EQ(part_2(), 349975);
    }
}