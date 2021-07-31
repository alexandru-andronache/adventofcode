#include "TestClass.h"
#include "../test.h"

namespace aocXXXX_day25 {
    TEST_F(TestsXXXXDay25, part_1_test) {
        ASSERT_EQ(part_1("../XXXX/day25/input_test.in"), 0);
    }

    TEST_F(TestsXXXXDay25, part_1_real_test) {
        ASSERT_EQ(part_1("../XXXX/day25/input.in"), 0);
    }
}
