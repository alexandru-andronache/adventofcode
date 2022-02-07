#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day24 {
    TEST_F(Tests2021Day24, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day24/input.in"), 94992994195998);
    }

    TEST_F(Tests2021Day24, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day24/input.in"), 21191861151161);
    }
}