#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day12 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2015/day12/input_test.in"), 3);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day12/input.in"), 111754);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2015/day12/input_test2.in"), 4);
    }

    TEST_F(TestClass, part_2_test_2) {
        ASSERT_EQ(part_2("../2015/day12/input_test3.in"), 0);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day12/input.in"), 65402);
    }
}