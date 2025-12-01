#include "file.h"
#include "utilities.h"
#include <vector>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aocXXXX_dayYY {
    int part_1(std::string_view path) {
        // std::string input = file::readFileAsString(path);
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int result = 0;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "");
        }

        return result;
    }

    int part_2(std::string_view path) {
        return 0;
    }
}

#ifdef TESTING
    TEST(TestXXXXDayYY, part_1_test) {
        ASSERT_EQ(aocXXXX_dayYY::part_1("../XXXX/dayYY/input_test.in"), 0);
    }

    TEST(TestXXXXDayYY, part_1_real_test) {
        ASSERT_EQ(aocXXXX_dayYY::part_1("../XXXX/dayYY/input.in"), 0);
    }

    TEST(TestXXXXDayYY, part_2_test) {
        ASSERT_EQ(aocXXXX_dayYY::part_2("../XXXX/dayYY/input_test.in"), 0);
    }

    TEST(TestXXXXDayYY, part_2_real_test) {
        ASSERT_EQ(aocXXXX_dayYY::part_2("../XXXX/dayYY/input.in"), 0);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aocXXXX_dayYY::part_1("../XXXX/dayYY/input.in"));
    fmt::print("Part 2: {}\n", aocXXXX_dayYY::part_2("../XXXX/dayYY/input.in"));

    return 0;
}
#endif
