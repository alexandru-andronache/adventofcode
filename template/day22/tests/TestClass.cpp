#include "TestClass.h"
#include "../test.h"

namespace aocXXXX_day22{
    TEST_F(TestsXXXXDay22, part_1_test) {
        ASSERT_EQ(part_1("../XXXX/day22/input_test.in"), 0);
    }

    TEST_F(TestsXXXXDay22, part_1_real_test) {
        ASSERT_EQ(part_1("../XXXX/day22/input.in"), 0);
    }

    TEST_F(TestsXXXXDay22, part_2_test) {
        ASSERT_EQ(part_2("../XXXX/day22/input_test.in"), 0);
    }

    TEST_F(TestsXXXXDay22, part_2_real_test) {
        ASSERT_EQ(part_2("../XXXX/day22/input.in"), 0);
    }
}