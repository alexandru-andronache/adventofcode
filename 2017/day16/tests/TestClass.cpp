#include "TestClass.h"
#include "../test.h"

namespace aoc2017_day16 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2017/day16/input_test.in", 5), "baedc");
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2017/day16/input.in"), "ionlbkfeajgdmphc");
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2017/day16/input_test.in", 5), "abcde");
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2017/day16/input.in"), "fdnphiegakolcmjb");
    }
}