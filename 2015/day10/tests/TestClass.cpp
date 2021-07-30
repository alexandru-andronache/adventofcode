#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day10{
    TEST_F(Tests2015Day10, part_1_test) {
        ASSERT_EQ(part_1("1"), 82350);
    }

    TEST_F(Tests2015Day10, part_1_real_test) {
        ASSERT_EQ(part_1("3113322113"), 329356);
    }

    TEST_F(Tests2015Day10, part_2_test) {
        ASSERT_EQ(part_2("1"), 1166642);
    }

    TEST_F(Tests2015Day10, part_2_real_test) {
        ASSERT_EQ(part_2("3113322113"), 4666278);
    }
}