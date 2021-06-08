#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day21 {
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2020/day21/input_test.in"), 5);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2020/day21/input_test.in"), "mxmxvkd,sqjhc,fvjkl");
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day21/input.in"), 1882);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day21/input.in"), "xgtj,ztdctgq,bdnrnx,cdvjp,jdggtft,mdbq,rmd,lgllb");
    }
}