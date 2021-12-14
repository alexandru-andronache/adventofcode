#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day14{
    TEST_F(Tests2021Day14, part_1_test) {
        ASSERT_EQ(part_1("../2021/day14/input_test.in"), 1588);
    }

    TEST_F(Tests2021Day14, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day14/input.in"), 2712);
    }

    TEST_F(Tests2021Day14, part_2_test) {
        ASSERT_EQ(part_2("../2021/day14/input_test.in"), 2188189693529);
    }

    TEST_F(Tests2021Day14, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day14/input.in"), 8336623059567);
    }
}