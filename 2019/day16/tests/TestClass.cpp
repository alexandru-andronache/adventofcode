#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day16 {
    TEST_F(Tests2019Day16, part_1_test) {
        ASSERT_EQ(part_1("../2019/day16/input_test.in"), "24176176");
    }

    TEST_F(Tests2019Day16, part_1_test_2) {
        ASSERT_EQ(part_1("../2019/day16/input_test2.in"), "73745418");
    }

    TEST_F(Tests2019Day16, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day16/input.in"), "59281788");
    }

    TEST_F(Tests2019Day16, part_2_test) {
        ASSERT_EQ(part_2("../2019/day16/input_test3.in"), "84462026");
    }

    TEST_F(Tests2019Day16, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day16/input.in"), "96062868");
    }
}