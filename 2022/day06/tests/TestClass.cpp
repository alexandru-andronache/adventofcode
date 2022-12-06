#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day06 {
    TEST_F(Tests2022Day06, part_1_test) {
        ASSERT_EQ(part_1("../2022/day06/input_test.in"), 5);
    }

    TEST_F(Tests2022Day06, part_1_test_2) {
        ASSERT_EQ(part_1("../2022/day06/input_test2.in"), 6);
    }

    TEST_F(Tests2022Day06, part_1_test_3) {
        ASSERT_EQ(part_1("../2022/day06/input_test3.in"), 10);
    }

    TEST_F(Tests2022Day06, part_1_test_4) {
        ASSERT_EQ(part_1("../2022/day06/input_test4.in"), 11);
    }

    TEST_F(Tests2022Day06, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day06/input.in"), 1892);
    }

    TEST_F(Tests2022Day06, part_2_test) {
        ASSERT_EQ(part_2("../2022/day06/input_test.in"), 23);
    }

    TEST_F(Tests2022Day06, part_2_test_2) {
        ASSERT_EQ(part_2("../2022/day06/input_test2.in"), 23);
    }

    TEST_F(Tests2022Day06, part_2_test_3) {
        ASSERT_EQ(part_2("../2022/day06/input_test3.in"), 29);
    }

    TEST_F(Tests2022Day06, part_2_test_4) {
        ASSERT_EQ(part_2("../2022/day06/input_test4.in"), 26);
    }

    TEST_F(Tests2022Day06, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day06/input.in"), 2313);
    }
}