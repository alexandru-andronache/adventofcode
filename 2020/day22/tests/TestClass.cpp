#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day22{
    TEST_F(Tests2020Day22, part_1_test) {
        ASSERT_EQ(part_1("../2020/day22/input_test.in"), 306);
    }

    TEST_F(Tests2020Day22, part_2_test) {
        ASSERT_EQ(part_2("../2020/day22/input_test.in"), 291);
    }

    TEST_F(Tests2020Day22, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day22/input.in"), 34664);
    }

    TEST_F(Tests2020Day22, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day22/input.in"), 32018);
    }
}