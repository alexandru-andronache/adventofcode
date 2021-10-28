#include "TestClass.h"

namespace aoc2019_day20 {
    TEST_F(Tests2019Day20, part_1_test) {
        ASSERT_EQ(part_1("../2019/day20/input_test.in"), 23);
    }

    TEST_F(Tests2019Day20, part_1_test_2) {
        ASSERT_EQ(part_1("../2019/day20/input_test2.in"), 58);
    }

    TEST_F(Tests2019Day20, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day20/input.in"), 442);
    }

    TEST_F(Tests2019Day20, part_2_test) {
        ASSERT_EQ(part_2("../2019/day20/input_test.in"), 26);
    }

    TEST_F(Tests2019Day20, part_2_test_2) {
        ASSERT_EQ(part_2("../2019/day20/input_test3.in"), 396);
    }

    TEST_F(Tests2019Day20, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day20/input.in"), 5208);
    }
}
