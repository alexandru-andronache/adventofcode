#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day02 {
    TEST_F(Tests2022Day02, part_1_test) {
        ASSERT_EQ(part_1("../2022/day02/input_test.in"), 15);
    }

    TEST_F(Tests2022Day02, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day02/input.in"), 11841);
    }

    TEST_F(Tests2022Day02, part_2_test) {
        ASSERT_EQ(part_2("../2022/day02/input_test.in"), 12);
    }

//    TEST_F(Tests2022Day02, part_2_real_test) {
//        ASSERT_EQ(part_2("../2022/day02/input.in"), 13022);
//    }
}