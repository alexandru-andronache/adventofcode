#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day14{
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2020/day14/input_test.in"), 165);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2020/day14/input_test2.in"), 208);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day14/input.in"), 17481577045893);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day14/input.in"), 4160009892257);
    }
}