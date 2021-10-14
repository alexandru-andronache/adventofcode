#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day13 {
    TEST_F(Tests2016Day13, part_1_test) {
        ASSERT_EQ(part_1(10, 7, 4), 11);
    }

    TEST_F(Tests2016Day13, part_1_real_test) {
        ASSERT_EQ(part_1(1358, 31, 39), 96);
    }

    TEST_F(Tests2016Day13, part_2_real_test) {
        ASSERT_EQ(part_2(1358), 141);
    }
}
