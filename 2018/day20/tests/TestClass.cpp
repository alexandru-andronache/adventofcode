#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day20 {
    TEST_F(Tests2018Day20, part_1_test) {
        ASSERT_EQ(part_1("../2018/day20/input_test.in"), 31);
    }

    TEST_F(Tests2018Day20, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day20/input.in"), 3669);
    }

    TEST_F(Tests2018Day20, part_2_real_test) {
        ASSERT_EQ(part_2("../2018/day20/input.in"), 8369);
    }
}
