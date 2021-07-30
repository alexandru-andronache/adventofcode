#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day04 {
    TEST_F(Tests2015Day04, part_1_test) {
        ASSERT_EQ(part_1("abcdef"), 609043);
    }

    TEST_F(Tests2015Day04, part_1_real_test) {
        ASSERT_EQ(part_1("ckczppom"), 117946);
    }

    TEST_F(Tests2015Day04, part_2_test) {
        ASSERT_EQ(part_2("abcdef"), 6742839);
    }

    TEST_F(Tests2015Day04, part_2_real_test) {
        ASSERT_EQ(part_2("ckczppom"), 3938038);
    }
}