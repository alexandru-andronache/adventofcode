#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day07{
    TEST_F(TestClass, part_1_test) {
        ASSERT_EQ(part_1("../2020/day07/input_test.in", "shiny gold", 10), 4);
    }

    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day07/input.in", "shiny gold"), 235);
    }

    TEST_F(TestClass, part_2_test) {
        ASSERT_EQ(part_2("../2020/day07/input_test.in", "shiny gold", 10), 32);
    }

    TEST_F(TestClass, part_2_test_second_example) {
        ASSERT_EQ(part_2("../2020/day07/input_test2.in", "shiny gold", 10), 126);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day07/input.in", "shiny gold"), 158493);
    }
}