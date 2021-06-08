#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day13 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2020/day13/input_test.in"), 295);
    }

    TEST_F(TestClass, part_2_test_1) {
        ASSERT_EQ(part_2("../2020/day13/input_test.in"), 1068781);
    }

    TEST_F(TestClass, part_2_test_2) {
        ASSERT_EQ(part_2("../2020/day13/input_test2.in"), 3417);
    }

    TEST_F(TestClass, part_2_test_3) {
        ASSERT_EQ(part_2("../2020/day13/input_test3.in"), 754018);
    }

    TEST_F(TestClass, part_2_test_4) {
        ASSERT_EQ(part_2("../2020/day13/input_test4.in"), 779210);
    }

    TEST_F(TestClass, part_2_test_5) {
        ASSERT_EQ(part_2("../2020/day13/input_test5.in"), 1261476);
    }

    TEST_F(TestClass, part_2_test_6) {
        ASSERT_EQ(part_2("../2020/day13/input_test6.in"), 1202161486);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day13/input.in"), 3385);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day13/input.in"), 600689120448303);
    }
}
