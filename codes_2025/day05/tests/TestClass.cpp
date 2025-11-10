#include "TestClass.h"
#include "../test.h"

namespace aoccodes_2025_day05 {
    TEST_F(Testscodes_2025Day05, part_1_test) {
        ASSERT_EQ(part_1("../codes_2025/day05/input_test.in"), 581078);
    }

    TEST_F(Testscodes_2025Day05, part_1_real_test) {
        ASSERT_EQ(part_1("../codes_2025/day05/input.in"), 2754578356);
    }

    TEST_F(Testscodes_2025Day05, part_2_test) {
        ASSERT_EQ(part_2("../codes_2025/day05/input_test_part_2.in"), 77053);
    }

    TEST_F(Testscodes_2025Day05, part_2_real_test) {
        ASSERT_EQ(part_2("../codes_2025/day05/input_part_2.in"), 8436060100176);
    }

    TEST_F(Testscodes_2025Day05, part_3_test) {
        ASSERT_EQ(part_3("../codes_2025/day05/input_test_part_3.in"), 260);
    }

    TEST_F(Testscodes_2025Day05, part_3_real_test) {
        ASSERT_EQ(part_3("../codes_2025/day05/input_part_3.in"), 31212509);
    }
}