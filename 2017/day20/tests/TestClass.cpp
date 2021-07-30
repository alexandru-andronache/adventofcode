#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day20 {
    TEST_F(Tests2017Day20, part_1_test) {
        ASSERT_EQ(part_1("../2017/day20/input_test.in"), 0);
    }

    TEST_F(Tests2017Day20, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day20/input.in"), 243);
    }

    TEST_F(Tests2017Day20, part_2_test) {
        ASSERT_EQ(part_2("../2017/day20/input_test2.in"), 1);
    }

    TEST_F(Tests2017Day20, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day20/input.in"), 648);
    }
}
