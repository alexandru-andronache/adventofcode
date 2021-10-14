#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day10{
    TEST_F(Tests2020Day10, part_1_test) {
        ASSERT_EQ(part_1("../2020/day10/input_test.in"), 35);
    }

    TEST_F(Tests2020Day10, part_1_test_2) {
        ASSERT_EQ(part_1("../2020/day10/input_test2.in"), 220);
    }

    TEST_F(Tests2020Day10, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day10/input.in"), 2080);
    }

    TEST_F(Tests2020Day10, part_2_test) {
        ASSERT_EQ(part_2("../2020/day10/input_test.in"), 8);
    }

    TEST_F(Tests2020Day10, part_2_test_2) {
        ASSERT_EQ(part_2("../2020/day10/input_test2.in"), 19208);
    }

    TEST_F(Tests2020Day10, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day10/input.in"), 6908379398144);
    }
}