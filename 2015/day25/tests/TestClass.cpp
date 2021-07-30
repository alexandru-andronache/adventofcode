#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day25 {
    TEST_F(Tests2015Day25, part_1_test) {
        ASSERT_EQ(part_1(2, 2), 21629792);
    }

    TEST_F(Tests2015Day25, part_1_test_2) {
        ASSERT_EQ(part_1(6, 5), 1534922);
    }

    TEST_F(Tests2015Day25, part_1_real_test) {
        ASSERT_EQ(part_1(2978, 3083), 2650453);
    }
}
