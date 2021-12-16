#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day16 {
    TEST_F(Tests2021Day16, part_1_test) {
        ASSERT_EQ(part_1("../2021/day16/input_test.in"), 16);
    }

    TEST_F(Tests2021Day16, part_1_test_2) {
        ASSERT_EQ(part_1("../2021/day16/input_test2.in"), 12);
    }

    TEST_F(Tests2021Day16, part_1_test_3) {
        ASSERT_EQ(part_1("../2021/day16/input_test3.in"), 23);
    }

    TEST_F(Tests2021Day16, part_1_test_4) {
        ASSERT_EQ(part_1("../2021/day16/input_test4.in"), 31);
    }

    TEST_F(Tests2021Day16, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day16/input.in"), 955);
    }

    TEST_F(Tests2021Day16, part_2_test) {
        ASSERT_EQ(part_2("../2021/day16/input_test5.in"), 1);
    }

    TEST_F(Tests2021Day16, part_2_test_2) {
        ASSERT_EQ(part_2("../2021/day16/input_test6.in"), 0);
    }

    TEST_F(Tests2021Day16, part_2_test_3) {
        ASSERT_EQ(part_2("../2021/day16/input_test7.in"), 9);
    }

    TEST_F(Tests2021Day16, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day16/input.in"), 158135423448);
    }
}