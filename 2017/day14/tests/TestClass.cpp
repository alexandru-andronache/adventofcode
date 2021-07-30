#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day14{
    TEST_F(Tests2017Day14, part_1_test) {
        ASSERT_EQ(part_1("flqrgnkx"), 8108);
    }

    TEST_F(Tests2017Day14, part_1_real_test) {
        ASSERT_EQ(part_1("stpzcrnm"), 8250);
    }

    TEST_F(Tests2017Day14, part_2_test) {
        ASSERT_EQ(part_2("flqrgnkx"), 1242);
    }

    TEST_F(Tests2017Day14, part_2_real_test) {
        ASSERT_EQ(part_2("stpzcrnm"), 1113);
    }
}