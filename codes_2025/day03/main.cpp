#include "file.h"
#include <fmt/printf.h>
#include "utilities.h"

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoccodes_2025_day03 {
    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::vector<int> nr = utils::splitStringToInt(input, ",");
        std::sort(nr.begin(), nr.end(), std::greater<int>());
        int sum = 0;
        int max = std::numeric_limits<int>::max();
        for (const auto& n : nr) {
            if (n < max) {
                sum += n;
                max = n;
            }
        }
        return sum;
    }

    unsigned long long part_2(std::string_view path, int crates = 20) {
        std::string input = file::readFileAsString(path);
        std::vector<int> nr = utils::splitStringToInt(input, ",");
        std::sort(nr.begin(), nr.end());
        int sum = 0;
        int count = 0;
        int min = std::numeric_limits<int>::min();
        for (const auto& n : nr) {
            if (n > min) {
                sum += n;
                min = n;
                count++;
            }
            if (count == crates) {
                return sum;
            }
        }
        return 0;
    }

    unsigned long long part_3(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::vector<int> nr = utils::splitStringToInt(input, ",");
        std::sort(nr.begin(), nr.end(), std::greater<int>());
        int count = 0;
        while (!nr.empty()) {
            std::vector<int> reminder;
            int max = std::numeric_limits<int>::max();
            for (const auto& n : nr) {
                if (n < max) {
                    max = n;
                }
                else {
                    reminder.push_back(n);
                }
            }
            count++;
            nr = reminder;
        }

        return count;
    }
}

#ifdef TESTING
namespace aoccodes_2025_day03 {
    TEST(Testscodes_2025Day03, part_1_test) {
        ASSERT_EQ(part_1("../codes_2025/day03/input/input_part_1_test.in"), 29);
    }

    TEST(Testscodes_2025Day03, part_1_real_test) {
        ASSERT_EQ(part_1("../codes_2025/day03/input/input_part_1.in"), 2692);
    }

    TEST(Testscodes_2025Day03, part_2_test) {
        ASSERT_EQ(part_2("../codes_2025/day03/input/input_part_2_test.in"), 781);
    }

    TEST(Testscodes_2025Day03, part_2_real_test) {
        ASSERT_EQ(part_2("../codes_2025/day03/input/input_part_2.in"), 264);
    }

    TEST(Testscodes_2025Day03, part_3_test) {
        ASSERT_EQ(part_3("../codes_2025/day03/input/input_part_3_test.in"), 3);
    }

    TEST(Testscodes_2025Day03, part_3_real_test) {
        ASSERT_EQ(part_3("../codes_2025/day03/input/input_part_3.in"), 3510);
    }
}
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoccodes_2025_day03::part_1("../codes_2025/day03/input/input_part_1.in"));
    fmt::print("Part 2: {}\n", aoccodes_2025_day03::part_2("../codes_2025/day03/input/input_part_2.in"));
    fmt::print("Part 3: {}\n", aoccodes_2025_day03::part_3("../codes_2025/day03/input/input_part_3.in"));

    return 0;
}
#endif
