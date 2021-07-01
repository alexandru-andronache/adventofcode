#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day03 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2019/day03/input_test.in"), 159);
    }

    TEST_F(TestClass, part_1_test_2) {
        ASSERT_EQ(part_1("../2019/day03/input_test2.in"), 135);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day03/input.in"), 2180);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2019/day03/input_test.in"), 610);
    }

    TEST_F(TestClass, part_2_test_2) {
        ASSERT_EQ(part_2("../2019/day03/input_test2.in"), 410);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day03/input.in"), 112316);
    }
}