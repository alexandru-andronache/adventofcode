#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day16 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2020/day16/input_test.in"), 71);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2020/day16/input_test2.in"), 1716);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day16/input.in"), 20975);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day16/input.in"), 910339449193);
    }
}