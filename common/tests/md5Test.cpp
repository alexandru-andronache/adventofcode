#include "md5Test.h"
#include "md5.h"

using namespace md5;

TEST_F(MD5, calculate_md5)
{
    ASSERT_EQ(calculateMD5("abcdef609043"), "000001dbbfa3a5c83a2d506429c7b00e");
    ASSERT_EQ(calculateMD5("pqrstuv1048970"), "000006136ef2ff3b291c85725f17325c");
}