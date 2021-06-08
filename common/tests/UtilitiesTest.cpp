#include "UtilitiesTest.h"
#include "utilities.h"

using namespace utils;

TEST_F(UtilitiesTest, test_is_number) {
    ASSERT_EQ(isInteger("12"), true);
    ASSERT_EQ(isInteger("0"), true);
    ASSERT_EQ(isInteger("123"), true);
}

TEST_F(UtilitiesTest, test_is_number_negativ) {
    ASSERT_EQ(isInteger("-12"), true);
    ASSERT_EQ(isInteger("-122"), true);
}

TEST_F(UtilitiesTest, test_is_not_number) {
    ASSERT_EQ(isInteger("-12a"), false);
    ASSERT_EQ(isInteger("--122"), false);
    ASSERT_EQ(isInteger("a1sf22"), false);
}

TEST_F(UtilitiesTest, find_number_in_string) {
    int pos = 2;
    int nr = getNumber("as23456dfsd", pos);
    ASSERT_EQ(nr, 23456);
    ASSERT_EQ(pos, 7);
}

TEST_F(UtilitiesTest, find_negative_number_in_string) {
    int pos = 2;
    int nr = getNumber("as-23456dfsd", pos);
    ASSERT_EQ(nr, -23456);
    ASSERT_EQ(pos, 8);
}

TEST_F(UtilitiesTest, split_string) {
    ASSERT_THAT(splitString("dask dslfkds,. fdsfsd-ds-", ",.- "), testing::ElementsAre("dask", "dslfkds", "fdsfsd", "ds"));
}

TEST_F(UtilitiesTest, decimal_to_int_from_str) {
    ASSERT_EQ(decimalToInt("10101"), 21);
    ASSERT_EQ(decimalToInt("XCCXX", 'X'), 19);
}

TEST_F(UtilitiesTest, decimal_to_int_from_vector) {
    ASSERT_EQ(decimalToInt({true, false, true, false, true, false}), 42);
}