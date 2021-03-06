#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day11 {
    TEST_F(Tests2015Day11, part_1_test) {
        ASSERT_EQ(part_1("abcdefgh"), "abcdffaa");
    }

    TEST_F(Tests2015Day11, part_1_test_2) {
        ASSERT_EQ(part_1("ghijklmn"), "ghjaabcc");
    }

    TEST_F(Tests2015Day11, part_1_real_test) {
        ASSERT_EQ(part_1("cqjxjnds"), "cqjxxyzz");
    }

    TEST_F(Tests2015Day11, part_2_real_test) {
        ASSERT_EQ(part_2("cqjxjnds"), "cqkaabcc");
    }
}