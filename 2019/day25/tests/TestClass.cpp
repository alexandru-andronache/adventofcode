#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day25 {
    TEST_F(Tests2019Day25, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day25/input.in"), 805307408);
    }
}
