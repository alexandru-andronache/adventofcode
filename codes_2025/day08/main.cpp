#include "file.h"
#include "utilities.h"
#include <map>
#include <ranges>
#include <utility>
#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoccodes_2025_day08 {

    unsigned long long part_1(std::string_view path) {
        std::vector<long long> numbers = file::readFileAsArrayLongLong(path, ",");
        long long max = *std::max_element(numbers.begin(), numbers.end());
        unsigned long long sol = 0;

        for (int i = 0; i < numbers.size() - 1; i++) {
            if (std::abs(numbers[i] - numbers[i + 1]) == max / 2) {
                sol++;
            }
        }
        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<long long> numbers = file::readFileAsArrayLongLong(path, ",");
        std::vector<std::pair<unsigned long long, unsigned long long>> pairs;
        unsigned long long sol = 0;
        for (int i = 0; i < numbers.size() - 1; i++) {
            std::pair<unsigned long long, unsigned long long> p{
                std::min(numbers[i], numbers[i + 1]),
                std::max(numbers[i], numbers[i + 1])};
            for (const auto& pair : pairs) {
                if (p.first > pair.first && p.first < pair.second &&
                    p.second > pair.second) {
                    sol++;
                }
                if (p.second > pair.first && p.second < pair.second &&
                    p.first < pair.first) {
                    sol++;
                }
            }
            pairs.emplace_back(p.first, p.second);
        }

        return sol;
    }

    unsigned long long part_3(std::string_view path) {
        std::vector<long long> numbers = file::readFileAsArrayLongLong(path, ",");
        unsigned long long max = *std::max_element(numbers.begin(), numbers.end());
        std::vector<std::vector<int>> grid(max + 1, std::vector<int>(max + 1, 0));
        for (int i = 0; i < numbers.size() - 1; i++) {
            grid[numbers[i]][numbers[i + 1]]++;
            grid[numbers[i + 1]][numbers[i]]++;
        }

        int sol = 0;
        for (int i = 1; i <= max; i++) {
            for (int j = i + 1; j <= max; j++) {
                int count = 0;
                for (int k = i + 1; k < j; k++) {
                    for (int l = 1; l < i; l++) {
                        count += grid[k][l];
                    }
                    for (int l = j + 1; l <= max; l++) {
                        count += grid[k][l];
                    }
                }
                count += grid[i][j];
                sol = std::max(sol, count);
            }
        }

        return sol;
    }
}

#ifdef TESTING
namespace aoccodes_2025_day08 {
    TEST(Testscodes_2025Day08, part_1_test) {
        ASSERT_EQ(part_1("../codes_2025/day08/input/input_part_1_test.in"), 4);
    }

    TEST(Testscodes_2025Day08, part_1_real_test) {
        ASSERT_EQ(part_1("../codes_2025/day08/input/input_part_1.in"), 57);
    }

    TEST(Testscodes_2025Day08, part_2_test) {
        ASSERT_EQ(part_2("../codes_2025/day08/input/input_part_2_test.in"), 21);
    }

    TEST(Testscodes_2025Day08, part_2_real_test) {
        ASSERT_EQ(part_2("../codes_2025/day08/input/input_part_2.in"), 2922530);
    }

    TEST(Testscodes_2025Day08, part_3_test) {
        ASSERT_EQ(part_3("../codes_2025/day08/input/input_part_3_test.in"), 7);
    }

    TEST(Testscodes_2025Day08, part_3_real_test) {
        ASSERT_EQ(part_3("../codes_2025/day08/input/input_part_3.in"), 2799);
    }
}
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoccodes_2025_day08::part_1("../codes_2025/day08/input/input_part_1.in"));
    fmt::print("Part 2: {}\n", aoccodes_2025_day08::part_2("../codes_2025/day08/input/input_part_2.in"));
    fmt::print("Part 3: {}\n", aoccodes_2025_day08::part_3("../codes_2025/day08/input/input_part_3.in"));

    return 0;
}
#endif
