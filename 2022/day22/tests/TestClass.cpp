#include "TestClass.h"
#include "../test.h"

namespace aoc2022_day22{
    TEST_F(Tests2022Day22, part_1_test) {
        ASSERT_EQ(part_1("../2022/day22/input_test.in"), 6032);
    }

    TEST_F(Tests2022Day22, part_1_real_test) {
        ASSERT_EQ(part_1("../2022/day22/input.in"), 197160);
    }

//    TEST_F(Tests2022Day22, part_2_test) {
//        ASSERT_EQ(part_2("../2022/day22/input_test.in", 4), 5031);
//    }

    TEST_F(Tests2022Day22, part_2_real_test) {
        ASSERT_EQ(part_2("../2022/day22/input.in", 50), 145065);
    }
}