#include "TestClass.h"
#include "../test.h"

namespace aoc2019_day22{
    TEST_F(Tests2019Day22, part_1_test) {
        ASSERT_EQ(part_1("../2019/day22/input_test.in", 10, 2), 1);
    }

    TEST_F(Tests2019Day22, part_1_test_2) {
        ASSERT_EQ(part_1("../2019/day22/input_test2.in", 10, 4), 0);
    }

    TEST_F(Tests2019Day22, part_1_real_test) {
        ASSERT_EQ(part_1("../2019/day22/input.in"), 6289);
    }

    TEST_F(Tests2019Day22, part_2_real_test) {
        ASSERT_EQ(part_2("../2019/day22/input.in"), 58348342289943);
    }
}