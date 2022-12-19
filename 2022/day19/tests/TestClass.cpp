#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day19 {
    TEST_F(Tests2022Day19, part_1_test) {
        ASSERT_EQ(part_1("../2022/day19/input_test.in"), 33);
    }

    TEST_F(Tests2022Day19, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day19/input.in"), 1589);
    }

    TEST_F(Tests2022Day19, part_2_test) {
        ASSERT_EQ(part_2("../2022/day19/input_test.in"), 0);
    }

    TEST_F(Tests2022Day19, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day19/input.in"), 29348);
    }
}