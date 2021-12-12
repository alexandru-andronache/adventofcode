#include "StringToIntMapTest.h"
#include <StringToIntMap.h>

using namespace stringtointmap;

TEST_F(StringToIntMapTest, add_string_test_get_index)
{
    StringToIntMap t;
    t.addString("aaa");
    t.addString("bbb");

    ASSERT_EQ(t.getIndex("aaa"), 0);
    ASSERT_EQ(t.getIndex("ccc"), -1);
}

TEST_F(StringToIntMapTest, add_string_test_get_string)
{
    StringToIntMap t;
    t.addString("aaa");
    t.addString("bbb");

    ASSERT_EQ(t.getString(1), "bbb");
    ASSERT_EQ(t.getString(2), "");
}