#include "StringTest.h"
#include "string_util.h"

using namespace string;

TEST_F(StringTest, findNumberOfSubstrings)
{
    ASSERT_EQ(findNumberOfSubstrings("aaaa", "aa"), 3);
    ASSERT_EQ(findNumberOfSubstrings("ababab", "bab"), 2);
    ASSERT_EQ(findNumberOfSubstrings("abcbaa", "abc"), 1);
}
