#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day05 {
    TEST_F(Tests2020Day05, processSeat_first_example) {
        auto result = processSeat("FBFBBFFRLR");
        ASSERT_TRUE(result.first == 44 && result.second == 5);
    }

    TEST_F(Tests2020Day05, processSeat_second_example) {
        auto result1 = processSeat("BFFFBBFRRR");
        auto result2 = processSeat("FFFBBBFRRR");
        auto result3 = processSeat("BBFFBBFRLL");

        ASSERT_TRUE(result1.first == 70 && result1.second == 7);
        ASSERT_TRUE(result2.first == 14 && result2.second == 7);
        ASSERT_TRUE(result3.first == 102 && result3.second == 4);
    }

    TEST_F(Tests2020Day05, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day05/input.in"), 978);
    }

    TEST_F(Tests2020Day05, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day05/input.in"), 727);
    }
}