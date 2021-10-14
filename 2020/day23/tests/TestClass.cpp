#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day23 {
    TEST_F(Tests2020Day23, part_1_test) {
        ASSERT_EQ(part_1(389125467, 10), 92658374);
    }

    TEST_F(Tests2020Day23, part_1_large_test) {
        ASSERT_EQ(part_1(389125467, 100), 67384529);
    }

    TEST_F(Tests2020Day23, part_2_test) {
        ASSERT_EQ(part_2(389125467), 149245887792);
    }

    TEST_F(Tests2020Day23, part_1_real_test) {
        ASSERT_EQ(part_1(653427918, 100), 76952348);
    }

    TEST_F(Tests2020Day23, part_2_real_test) {
        ASSERT_EQ(part_2(653427918), 72772522064);
    }
}
