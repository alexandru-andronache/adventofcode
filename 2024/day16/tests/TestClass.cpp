#include "TestClass.h"
#include "../test.h"

namespace aoc2024_day16 {
    TEST_F(Tests2024Day16, part_1_test) {
        ASSERT_EQ(part_1("../2024/day16/input_test.in"), 7036);
    }

    TEST_F(Tests2024Day16, part_1_second_test) {
        ASSERT_EQ(part_1("../2024/day16/input_test_second_example.in"), 11048);
    }

    TEST_F(Tests2024Day16, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day16/input.in"), 95444);
    }

    TEST_F(Tests2024Day16, part_2_test) {
        ASSERT_EQ(part_2("../2024/day16/input_test.in"), 45);
    }

    TEST_F(Tests2024Day16, part_2_second_test) {
        ASSERT_EQ(part_2("../2024/day16/input_test_second_example.in"), 64);
    }

    TEST_F(Tests2024Day16, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day16/input.in"), 513);
    }
}