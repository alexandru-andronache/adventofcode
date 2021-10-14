#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day19 {
    TEST_F(Tests2016Day19, part_1_test) {
        ASSERT_EQ(part_1(5), 3);
    }

    TEST_F(Tests2016Day19, part_1_real_test) {
        ASSERT_EQ(part_1(3001330), 1808357);
    }

    TEST_F(Tests2016Day19, part_2_test) {
        ASSERT_EQ(part_2(5), 2);
    }

    TEST_F(Tests2016Day19, part_2_real_test) {
        ASSERT_EQ(part_2(3001330), 1407007);
    }
}