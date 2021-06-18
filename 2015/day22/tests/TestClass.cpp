#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day22{
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1(55, 8, 50, 500), 953);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2(55, 8, 50, 500), 1289);
    }
}