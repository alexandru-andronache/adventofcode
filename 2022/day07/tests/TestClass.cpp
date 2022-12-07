#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day07 {
    TEST_F(Tests2022Day07, part_1_test) {
        ASSERT_EQ(part_1("../2022/day07/input_test.in"), 95437);
    }

    TEST_F(Tests2022Day07, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day07/input.in"), 1644735);
    }

    TEST_F(Tests2022Day07, part_2_test) {
        ASSERT_EQ(part_2("../2022/day07/input_test.in"), 24933642);
    }

    TEST_F(Tests2022Day07, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day07/input.in"), 1300850);
    }
}