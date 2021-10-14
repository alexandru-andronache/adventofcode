#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day12 {
    TEST_F(Tests2020Day12, part_1_test) {
        ASSERT_EQ(part_1("../2020/day12/input_test.in"), 25);
    }

    TEST_F(Tests2020Day12, part_2_test) {
        ASSERT_EQ(part_2("../2020/day12/input_test.in"), 286);
    }

    TEST_F(Tests2020Day12, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day12/input.in"), 2228);
    }

    TEST_F(Tests2020Day12, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day12/input.in"), 42908);
    }
}