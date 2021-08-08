#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day14{
    TEST_F(Tests2018Day14, part_1_test) {
        ASSERT_EQ(part_1(5), "0124515891");
    }

    TEST_F(Tests2018Day14, part_1_test_2) {
        ASSERT_EQ(part_1(18), "9251071085");
    }

    TEST_F(Tests2018Day14, part_1_test_3) {
        ASSERT_EQ(part_1(2018), "5941429882");
    }

    TEST_F(Tests2018Day14, part_1_real_test) {
        ASSERT_EQ(part_1(637061), "3138510102");
    }

    TEST_F(Tests2018Day14, part_2_test) {
        ASSERT_EQ(part_2(51589), 9);
    }

    TEST_F(Tests2018Day14, part_2_test_2) {
        ASSERT_EQ(part_2(92510), 18);
    }

    TEST_F(Tests2018Day14, part_2_test_3) {
        ASSERT_EQ(part_2(59414), 2018);
    }

    TEST_F(Tests2018Day14, part_2_real_test) {
        ASSERT_EQ(part_2(637061), 20179081);
    }
}