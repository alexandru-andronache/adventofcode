#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day20 {
    TEST_F(Tests2016Day20, part_1_test) {
        ASSERT_EQ(part_1("../2016/day20/input_test.in"), 3);
    }

    TEST_F(Tests2016Day20, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day20/input.in"), 32259706);
    }

    TEST_F(Tests2016Day20, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day20/input.in"), 113);
    }
}
