#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day05 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("abc"), "18f47a30");
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("cxdnnyjw"), "f77a0e6e");
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("abc"), "05ace8e3");
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("cxdnnyjw"), "999828ec");
    }
}