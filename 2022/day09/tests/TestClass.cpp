#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day09 {
    TEST_F(Tests2022Day09, part_1_test) {
        ASSERT_EQ(part_1("../2022/day09/input_test.in"), 13);
    }

    TEST_F(Tests2022Day09, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day09/input.in"), 6314);
    }

    TEST_F(Tests2022Day09, part_2_test) {
        ASSERT_EQ(part_2("../2022/day09/input_test.in"), 1);
    }

    TEST_F(Tests2022Day09, part_2_test_2) {
        ASSERT_EQ(part_2("../2022/day09/input_test2.in"), 36);
    }

    TEST_F(Tests2022Day09, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day09/input.in"), 2504);
    }
}
