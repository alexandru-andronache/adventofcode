#include "TestClass.h"
#include "../test.h"

namespace aoc2018_day25 {
    TEST_F(Tests2018Day25, part_1_test) {
        ASSERT_EQ(part_1("../2018/day25/input_test.in"), 0);
    }

    TEST_F(Tests2018Day25, part_1_real_test) {
        ASSERT_EQ(part_1("../2018/day25/input.in"), 0);
    }
}
