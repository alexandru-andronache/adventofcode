#include "TestClass.h"
#include "../test.h"

namespace aoc2016_day17{
    TEST_F(Tests2016Day17, part_1_test) {
        ASSERT_EQ(part_1("ihgpwlah"), "DDRRRD");
    }

    TEST_F(Tests2016Day17, part_1_test_2) {
        ASSERT_EQ(part_1("kglvqrro"), "DDUDRLRRUDRD");
    }

    TEST_F(Tests2016Day17, part_1_test_3) {
        ASSERT_EQ(part_1("ulqzkmiv"), "DRURDRUDDLLDLUURRDULRLDUUDDDRR");
    }

    TEST_F(Tests2016Day17, part_1_real_test) {
        ASSERT_EQ(part_1("yjjvjgan"), "RLDRUDRDDR");
    }

    TEST_F(Tests2016Day17, part_2_test) {
        ASSERT_EQ(part_2("ihgpwlah"), 370);
    }

    TEST_F(Tests2016Day17, part_2_test_2) {
        ASSERT_EQ(part_2("kglvqrro"), 492);
    }

    TEST_F(Tests2016Day17, part_2_test_3) {
        ASSERT_EQ(part_2("ulqzkmiv"), 830);
    }

    TEST_F(Tests2016Day17, part_2_real_test) {
        ASSERT_EQ(part_2("yjjvjgan"), 498);
    }
}