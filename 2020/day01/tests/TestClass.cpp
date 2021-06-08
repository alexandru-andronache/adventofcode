#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day01 {
    TEST_F(TestClass2020_01, part_1_test) {
        ASSERT_EQ(part_1("../2020/day01/input_test.in"), 514579);
    }

    TEST_F(TestClass2020_01, part_1_real) {
        ASSERT_EQ(part_1("../2020/day01/input.in"), 319531);
    }

    TEST_F(TestClass2020_01, part_2_test) {
        ASSERT_EQ(part_2("../2020/day01/input_test.in"), 241861950);
    }

    TEST_F(TestClass2020_01, part_2_real) {
        ASSERT_EQ(part_2("../2020/day01/input.in"), 244300320);
    }
}