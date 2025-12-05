#include "RangesTest.h"

TEST_F(RangesTests, testIfNumberInsideRange) {
    aoc::Ranges<int> ranges;
    ranges.addRange(3, 5);
    ranges.addRange(10, 14);
    ranges.addRange(16, 20);
    ranges.addRange(12, 18);
    ASSERT_TRUE(ranges.isInRange(5));
    ASSERT_TRUE(ranges.isInRange(11));
    ASSERT_TRUE(ranges.isInRange(17));
    ASSERT_FALSE(ranges.isInRange(1));
    ASSERT_FALSE(ranges.isInRange(8));
    ASSERT_FALSE(ranges.isInRange(32));
}

TEST_F(RangesTests, testCount) {
    aoc::Ranges<int> ranges;
    ranges.addRange(3, 5);
    ranges.addRange(10, 14);
    ranges.addRange(16, 20);
    ranges.addRange(12, 18);
    ASSERT_EQ(ranges.count(), 14);
}