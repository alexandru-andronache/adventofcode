#include "TestClass.h"
#include "../test.h"

namespace aocXXXX_day10{
    TEST_F(TestsXXXXDay10, part_1_test) {
        ASSERT_EQ(part_1("../XXXX/day10/input_test.in"), 0);
    }

    TEST_F(TestsXXXXDay10, part_1_real_test) {
        ASSERT_EQ(part_1("../XXXX/day10/input.in"), 0);
    }

    TEST_F(TestsXXXXDay10, part_2_test) {
        ASSERT_EQ(part_2("../XXXX/day10/input_test.in"), 0);
    }

    TEST_F(TestsXXXXDay10, part_2_real_test) {
        ASSERT_EQ(part_2("../XXXX/day10/input.in"), 0);
    }
}