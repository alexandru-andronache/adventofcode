#include <numeric>

#include "file.h"
#include "utilities.h"
#include <vector>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day06 {
    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        unsigned long long result = 0;
        std::vector<std::vector<unsigned long long>> data;

        for (int i = 0; i < lines.size() - 1; ++i) {
            data.push_back(utils::splitStringToULL(lines[i],  " "));
        }
        std::vector<std::string> tokens = utils::splitString(lines.back(),  " ");
        for (int i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == "+") {
               result += std::accumulate(data.begin(), data.end(), 0ULL, [i](auto s, const auto& col) {
                    return s + col[i];
               });
            }
            else if (tokens[i] == "*") {
                result += std::accumulate(data.begin(), data.end(), 1ULL, [i](auto s, const auto& col) {
                    return s * col[i];
                });
            }
        }

        return result;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        unsigned long long result = 0;
        std::vector<unsigned long long> currentNumbers;

        char current_op;
        int index = 0;
        int max = 0;
        for (int i = 0; i < lines.size() - 1; ++i) {
            max = std::max(max, static_cast<int>(lines[i].size()));
        }

        for (int i = 0; i < max; ++i) {
            std::vector<char> column;
            bool space = true;
            for (int j = 0; j < lines.size() - 1; ++j) {
                if (lines[j][i] - '0' >= 0 && lines[j][i] - '0' <= 9) {
                    column.push_back(lines[j][i]);
                }
                space = space && (lines[j][i] == ' ');
            }
            if (lines.back()[i] == '+' || lines.back()[i] == '*') {
                current_op = lines.back()[i];
            }
            if (!space) {
                currentNumbers.push_back(0);
                for (const auto& j : column) {
                    currentNumbers[index] = currentNumbers[index] * 10 + (j - '0');
                }
                index++;
            }
            else {
                if (current_op == '+') {
                    result += std::accumulate(currentNumbers.begin(), currentNumbers.end(), 0ULL, std::plus<unsigned long long>());
                }
                else if (current_op == '*') {
                    result += std::accumulate(currentNumbers.begin(), currentNumbers.end(), 1ULL, std::multiplies<unsigned long long>());
                }
                currentNumbers.clear();
                index = 0;
            }
        }

        if (current_op == '+') {
            result += std::accumulate(currentNumbers.begin(), currentNumbers.end(), 0ULL, std::plus<unsigned long long>());
        }
        else if (current_op == '*') {
            result += std::accumulate(currentNumbers.begin(), currentNumbers.end(), 1ULL, std::multiplies<unsigned long long>());
        }

        return result;
    }
}

#ifdef TESTING
    TEST(Test2025Day06, part_1_test) {
        ASSERT_EQ(aoc2025_day06::part_1("../2025/day06/input_test.in"), 4277556);
    }

    TEST(Test2025Day06, part_1_real_test) {
        ASSERT_EQ(aoc2025_day06::part_1("../2025/day06/input.in"), 5552221122013);
    }

    TEST(Test2025Day06, part_2_test) {
        ASSERT_EQ(aoc2025_day06::part_2("../2025/day06/input_test.in"), 3263827);
    }

    TEST(Test2025Day06, part_2_real_test) {
        ASSERT_EQ(aoc2025_day06::part_2("../2025/day06/input.in"), 11371597126232);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day06::part_1("../2025/day06/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day06::part_2("../2025/day06/input.in"));

    return 0;
}
#endif
