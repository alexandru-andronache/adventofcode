#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day21 {
    TEST_F(Tests2021Day21, part_1_test) {
        ASSERT_EQ(part_1(4, 8), 739785);
    }

    TEST_F(Tests2021Day21, part_1_real_test) {
        ASSERT_EQ(part_1(4, 7), 893700);
    }

    TEST_F(Tests2021Day21, part_2_test) {
        ASSERT_EQ(part_2(4, 8), 444356092776315);
    }

    TEST_F(Tests2021Day21, part_2_real_test) {
        ASSERT_EQ(part_2(4, 7), 568867175661958);
    }
}