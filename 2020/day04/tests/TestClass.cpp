#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day04 {
    TEST_F(Tests2020Day04, part_1_test) {
        ASSERT_EQ(part_1("../2020/day04/input_test_1.in"), 2);
    }

    TEST_F(Tests2020Day04, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day04/input.in"), 260);
    }

    TEST_F(Tests2020Day04, part_2_test_invalid) {
        ASSERT_EQ(part_2("../2020/day04/input_test_2.in"), 0);
    }

    TEST_F(Tests2020Day04, part_2_test_valid_passports) {
        ASSERT_EQ(part_2("../2020/day04/input_test_3.in"), 4);
    }

    TEST_F(Tests2020Day04, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day04/input.in"), 153);
    }
}