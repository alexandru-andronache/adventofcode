#include "TestClass.h"
#include "../test.h"

namespace aoccodes_2024_day23 {
    TEST_F(Testscodes_2024Day23, part_1_test) {
        ASSERT_EQ(part_1("../codes_2024/day23/input_test.in"), 0);
    }

    TEST_F(Testscodes_2024Day23, part_1_real_test) {
        ASSERT_EQ(part_1("../codes_2024/day23/input.in"), 0);
    }

    TEST_F(Testscodes_2024Day23, part_2_test) {
        ASSERT_EQ(part_2("../codes_2024/day23/input_test.in"), 0);
    }

    TEST_F(Testscodes_2024Day23, part_2_real_test) {
        ASSERT_EQ(part_2("../codes_2024/day23/input.in"), 0);
    }
}
