#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day20 {
    TEST_F(Tests2021Day20, part_1_test) {
        ASSERT_EQ(part_1("../2021/day20/input_test.in"), 35);
    }

    TEST_F(Tests2021Day20, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day20/input.in"), 5573);
    }

    TEST_F(Tests2021Day20, part_2_test) {
        ASSERT_EQ(part_2("../2021/day20/input_test.in"), 3351);
    }

    TEST_F(Tests2021Day20, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day20/input.in"), 20097);
    }
}
