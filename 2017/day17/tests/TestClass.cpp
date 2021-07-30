#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day17{
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1(3), 638);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1(343), 1914);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2(343), 41797835);
    }
}