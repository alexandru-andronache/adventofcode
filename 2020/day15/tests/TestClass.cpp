#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day15 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2020/day15/input_test.in"), 436);
    }

    TEST_F(TestClass, part_1_test_2) {
        ASSERT_EQ(part_1("../2020/day15/input_test2.in"), 1836);
    }

    TEST_F(TestClass, part_1_test_3) {
        ASSERT_EQ(part_1("../2020/day15/input_test3.in"), 438);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day15/input.in"), 276);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2020/day15/input_test.in"), 175594);
    }

    TEST_F(TestClass, part_2_test_2) {
        ASSERT_EQ(part_2("../2020/day15/input_test2.in"), 362);
    }

    TEST_F(TestClass, part_2_test_3) {
        ASSERT_EQ(part_2("../2020/day15/input_test3.in"), 18);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day15/input.in"), 31916);
    }
}