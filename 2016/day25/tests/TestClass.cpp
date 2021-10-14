#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day25 {
    TEST_F(Tests2016Day25, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day25/input.in"), 175);
    }
}
