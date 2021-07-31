#include "TestClass.h"
#include "../test.h"

namespace aocXXXX_day12 {
    TEST_F(TestsXXXXDay12, part_1_test) {
        ASSERT_EQ(part_1("../XXXX/day12/input_test.in"), 0);
    }

    TEST_F(TestsXXXXDay12, part_1_real_test) {
        ASSERT_EQ(part_1("../XXXX/day12/input.in"), 0);
    }

    TEST_F(TestsXXXXDay12, part_2_test) {
        ASSERT_EQ(part_2("../XXXX/day12/input_test.in"), 0);
    }

    TEST_F(TestsXXXXDay12, part_2_real_test) {
        ASSERT_EQ(part_2("../XXXX/day12/input.in"), 0);
    }
}