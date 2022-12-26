#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day20 {
    TEST_F(Tests2022Day20, part_1_test) {
        ASSERT_EQ(part_1("../2022/day20/input_test.in"), 3);
    }

    TEST_F(Tests2022Day20, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day20/input.in"), 8764);
    }

    TEST_F(Tests2022Day20, part_2_test) {
        ASSERT_EQ(part_2("../2022/day20/input_test.in"), 1623178306);
    }

    TEST_F(Tests2022Day20, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day20/input.in"), 535648840980);
    }
}
