#include "file.h"
#include "utilities.h"
#include <vector>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day06 {
    unsigned long long part_1(std::string_view path) {
        // std::string input = file::readFileAsString(path);
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        unsigned long long result = 0;
        std::vector<std::vector<unsigned long long>> data;

        for (int i = 0; i < lines.size() - 1; ++i) {
            std::vector<std::string> tokens = utils::splitString(lines[i],  " ");
            std::vector<unsigned long long> data2;
            for (const auto& token : tokens) {
                data2.push_back(std::stoull(token));
            }
            data.push_back(data2);
        }
        std::vector<std::string> tokens = utils::splitString(lines.back(),  " ");
        for (int i = 0; i < tokens.size(); ++i) {
            if (tokens[i] == "+") {
                unsigned long long sum = 0;
                for (int j = 0; j < data.size(); ++j) {
                    sum += data[j][i];
                }
                result += sum;
            }
            else if (tokens[i] == "*") {
                unsigned long long p = 1;
                for (int j = 0; j < data.size(); ++j) {
                    p *= data[j][i];
                }
                result += p;
            }
        }

        return result;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        unsigned long long result = 0;
        std::vector<std::vector<unsigned long long>> data;
        std::vector<unsigned long long> data2;
        for (int i = 0; i < 100; ++i) {
            data2.push_back(0);
        }

        char current_op;
        int index = 0;
        int max = 0;
        for (int i = 0; i < lines.size() - 1; ++i) {
            if (lines[i].size() > max) {
                max = lines[i].size();
            }
        }

        for (int i = 0; i < max; ++i) {
            std::vector<char> column;
            bool space = true;
            for (int j = 0; j < lines.size() - 1; ++j) {
                column.push_back(lines[j][i]);
                if (lines[j][i] != ' ') {
                    space = false;
                }
            }
            if (lines.back()[i] == '+' || lines.back()[i] == '*') {
                current_op = lines.back()[i];
            }
            if (!space) {
                for (int j = 0; j < column.size(); ++j) {
                    if (column[j] - '0' < 0 || column[j] - '0' > 9) {
                        continue;
                    }
                    data2[index] = data2[index] * 10 + (column[j] - '0');
                }
                index++;
            }
            else {
                if (current_op == '+') {
                    unsigned long long sum = 0;
                    for (const auto& n : data2) {
                        sum += n;
                    }
                    result += sum;
                }
                else if (current_op == '*') {
                    unsigned long long p = 1;
                    for (const auto& n : data2) {
                        if (n > 0) {
                            p *= n;
                        }
                    }
                    result += p;
                }
                data2.clear();
                for (int k = 0; k < 100; ++k) {
                    data2.push_back(0);
                }
                index = 0;
            }
        }

        if (current_op == '+') {
            unsigned long long sum = 0;
            for (const auto& n : data2) {
                sum += n;
            }
            result += sum;
        }
        else if (current_op == '*') {
            unsigned long long p = 1;
            for (const auto& n : data2) {
                if (n > 0) {
                    p *= n;
                }
            }
            result += p;
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
