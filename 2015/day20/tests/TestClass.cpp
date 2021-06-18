#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day20 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1(36000000), 831600);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2(36000000), 884520);
    }
}
