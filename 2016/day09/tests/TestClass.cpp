#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day09 {
    TEST_F(Tests2016Day09, part_1_test) {
        ASSERT_EQ(part_1("../2016/day09/input_test.in"), 18);
    }

    TEST_F(Tests2016Day09, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day09/input.in"), 183269);
    }

    TEST_F(Tests2016Day09, part_2_test) {
        ASSERT_EQ(part_2("../2016/day09/input_test2.in"), 445);
    }

    TEST_F(Tests2016Day09, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day09/input.in"), 11317278863);
    }
}
