#include "TestClass.h"
#include "../test.h"

namespace aocXXXX_day04 {
    TEST_F(TestsXXXXDay04, part_1_test) {
        ASSERT_EQ(part_1("../XXXX/day04/input_test.in"), 0);
    }

    TEST_F(TestsXXXXDay04, part_1_real_test) {
        ASSERT_EQ(part_1("../XXXX/day04/input.in"), 0);
    }

    TEST_F(TestsXXXXDay04, part_2_test) {
        ASSERT_EQ(part_2("../XXXX/day04/input_test.in"), 0);
    }

    TEST_F(TestsXXXXDay04, part_2_real_test) {
        ASSERT_EQ(part_2("../XXXX/day04/input.in"), 0);
    }
}