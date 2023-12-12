#include "TestClass.h"
#include "../test.h"

namespace aoc2023_day12 {
    TEST_F(Tests2023Day12, part_1_test) {
        ASSERT_EQ(part_1("../2023/day12/input_test.in"), 21);
    }

//    TEST_F(Tests2023Day12, part_1_real_test) {
//        ASSERT_EQ(part_1("../2023/day12/input.in"), 8270);
//    }

    TEST_F(Tests2023Day12, part_2_test) {
        ASSERT_EQ(part_2("../2023/day12/input_test.in"), 525152);
    }

    TEST_F(Tests2023Day12, part_2_real_test) {
        ASSERT_EQ(part_2("../2023/day12/input.in"), 204640299929836);
    }
}