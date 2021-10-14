#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day20 {
    TEST_F(Tests2020Day20, part_1_test) {
        ASSERT_EQ(part_1("../2020/day20/input_test.in"), 20899048083289);
    }

    TEST_F(Tests2020Day20, part_2_test) {
        ASSERT_EQ(part_2("../2020/day20/input_test.in"), 273);
    }

    TEST_F(Tests2020Day20, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day20/input.in"), 45443966642567);
    }

    TEST_F(Tests2020Day20, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day20/input.in"), 1607);
    }
}
