#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day16 {
    TEST_F(Tests2016Day16, part_1_real_test) {
        ASSERT_EQ(part_1("00101000101111010"), "10010100110011100");
    }

    TEST_F(Tests2016Day16, part_2_real_test) {
        ASSERT_EQ(part_2("00101000101111010"), "01100100101101100");
    }
}