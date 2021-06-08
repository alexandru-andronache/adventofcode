#include "FileTest.h"
#include "file.h"

using namespace file;

TEST_F(FileTest, read_file)
{
    ASSERT_EQ(readFileAsString("input/test.in"), "dasfdsgfskhgfjsddskf289e23");
}

TEST_F(FileTest, read_file_as_vector_of_int)
{
    std::vector<int> input = readFileAsArrayInt("input/testArrayInt.in");
    ASSERT_EQ(input.size(), 4);
    ASSERT_THAT(input, testing::ElementsAre(23, 44, 356, 3));
}

TEST_F(FileTest, read_file_as_vector_of_int_with_separator)
{
    std::vector<long long> input = readFileAsArrayLongLong("input/testArrayIntWithSeparator.in", ",");
    ASSERT_EQ(input.size(), 9);
    ASSERT_THAT(input, testing::ElementsAre(3, 8, 1005, 8, 334, 1106, 0, -5, 1));
}

TEST_F(FileTest, read_file_as_vector_of_string)
{
    std::vector<std::string> output = readFileAsArrayString("input/testArrayInt.in");
    ASSERT_EQ(output.size(), 4);
    ASSERT_THAT(output, testing::ElementsAre("23", "44", "356", "3"));
}
