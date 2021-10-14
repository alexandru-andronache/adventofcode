#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day25 {
    TEST_F(Tests2020Day25, part_1_test) {
        ASSERT_EQ(part_1(5764801, 17807724), 14897079);
    }

    TEST_F(Tests2020Day25, part_1_real_test) {
        ASSERT_EQ(part_1(9789649, 3647239), 8740494);
    }
}
