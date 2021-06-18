#include "TestClass.h"
#include "../test.h"

namespace aoc2015_day16 {
    TEST_F(TestClass, part_1_real_test) {
        ASSERT_EQ(part_1("../2015/day16/input.in",{{"children", 3},
                                                   {"cats", 7},
                                                   {"samoyeds", 2},
                                                   {"pomeranians", 3},
                                                   {"akitas", 0},
                                                   {"vizslas", 0},
                                                   {"goldfish", 5},
                                                   {"trees", 3},
                                                   {"cars", 2},
                                                   {"perfumes", 1}}), 373);
    }

    TEST_F(TestClass, part_2_real_test) {
        ASSERT_EQ(part_2("../2015/day16/input.in",{{"children", 3},
                                                   {"cats", 7},
                                                   {"samoyeds", 2},
                                                   {"pomeranians", 3},
                                                   {"akitas", 0},
                                                   {"vizslas", 0},
                                                   {"goldfish", 5},
                                                   {"trees", 3},
                                                   {"cars", 2},
                                                   {"perfumes", 1}}), 260);
    }
}