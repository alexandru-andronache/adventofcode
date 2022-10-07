#include "TestClass.h"
#include "../test.h"

namespace aoc2021_day22{
    TEST_F(Tests2021Day22, part_1_test) {
        ASSERT_EQ(part_1("../2021/day22/input_test.in"), 39);
    }

    TEST_F(Tests2021Day22, part_1_test_2) {
        ASSERT_EQ(part_1("../2021/day22/input_test2.in"), 590784);
    }

    TEST_F(Tests2021Day22, part_1_real_test) {
        ASSERT_EQ(part_1("../2021/day22/input.in"), 648681);
    }

    TEST_F(Tests2021Day22, part_2_test) {
        ASSERT_EQ(part_2("../2021/day22/input_test3.in"), 2758514936282235);
    }

    TEST_F(Tests2021Day22, part_2_real_test) {
        ASSERT_EQ(part_2("../2021/day22/input.in"), 1302784472088899);
    }
}