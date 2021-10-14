#include "TestClass.h"
#include "../test.h"

namespace aoc2020_day24 {
    TEST_F(Tests2020Day24, part_1_test) {
        ASSERT_EQ(part_1("../2020/day24/input_test.in"), 10);
    }

    TEST_F(Tests2020Day24, part_2_test) {
        std::vector<int> days {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20};
        std::vector<int> results {15, 12, 25, 14, 23, 28, 41, 37, 49, 37, 132};
        for (int i = 0; i < days.size(); ++i) {
            ASSERT_EQ(part_2("../2020/day24/input_test.in", days[i]), results[i]);
        }
    }

    TEST_F(Tests2020Day24, part_1_real_test) {
        ASSERT_EQ(part_1("../2020/day24/input.in"), 438);
    }

    TEST_F(Tests2020Day24, part_2_real_test) {
        ASSERT_EQ(part_2("../2020/day24/input.in"), 4038);
    }
}