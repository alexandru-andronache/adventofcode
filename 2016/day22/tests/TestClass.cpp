#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day22{
    TEST_F(Tests2016Day22, part_1_real_test) {
        ASSERT_EQ(part_1("../2016/day22/input.in"), 955);
    }

    TEST_F(Tests2016Day22, part_2_real_test) {
        ASSERT_EQ(part_2("../2016/day22/input.in"), 246);
    }
}