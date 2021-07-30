#include "TestClass.h"
#include "../test.h"
#include <vector>

namespace aoc2017_day25 {
    TEST_F(Tests2017Day25, part_1_test) {
        ASSERT_EQ(part_1({{'A', {{1, 1, 'B'}, {0, -1, 'B'}}},
                          {'B',{{1, -1, 'A'}, {1, 1, 'A'}}}}, 6), 3);
    }

    TEST_F(Tests2017Day25, part_1_real_test) {
        ASSERT_EQ(part_1({{'A', {{1, 1, 'B'}, {0, -1, 'C'}}},
                          {'B', {{1, -1, 'A'}, {1, 1, 'D'}}},
                          {'C', {{1, 1, 'A'}, {0, -1, 'E'}}},
                          {'D', {{1, 1, 'A'}, {0, 1, 'B'}}},
                          {'E', {{1, -1, 'F'}, {1, -1, 'C'}}},
                          {'F', {{1, 1, 'D'}, {1, 1, 'A'}}}}), 2870);
    }
}
