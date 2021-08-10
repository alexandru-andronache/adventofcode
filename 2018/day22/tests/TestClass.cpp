#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day22{
    TEST_F(Tests2018Day22, part_1_test) {
        ASSERT_EQ(part_1(510, {10, 10}), 114);
    }

    TEST_F(Tests2018Day22, part_1_real_test) {
        ASSERT_EQ(part_1(5355, {14, 796}), 11972);
    }

    TEST_F(Tests2018Day22, part_2_test) {
        ASSERT_EQ(part_2(510, {10, 10}), 45);
    }

    TEST_F(Tests2018Day22, part_2_real_test) {
        ASSERT_EQ(part_2(5355, {14, 796}), 1092);
    }
}