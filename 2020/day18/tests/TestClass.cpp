#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day18 {
    TEST_F(Tests2020Day18, part_1_test) {
        ASSERT_EQ(part_1("../2020/day18/input_test.in"), 26335);
    }

    TEST_F(Tests2020Day18, part_2_test) {
        ASSERT_EQ(part_2("../2020/day18/input_test.in"), 693891);
    }

    TEST_F(Tests2020Day18, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day18/input.in"), 4297397455886);
    }

    TEST_F(Tests2020Day18, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day18/input.in"), 93000656194428);
    }
}