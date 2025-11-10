#include "file.h"
#include "utilities.h"
#include <algorithm>
#include <ranges>
#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoccodes_2025_day05 {
    struct row {
        int number;
        int left;
        int right;
    };

    std::vector<row> solve(const std::vector<int>& nr) {
        std::vector<row> rows;

        for (int i = 1; i < nr.size(); i++) {
            bool insert = false;
            for (auto& [number, left, right] : rows) {
                if (number > nr[i] && left == std::numeric_limits<int>::max()) {
                    insert = true;
                    left = nr[i];
                    break;
                }
                if (number < nr[i] && right == std::numeric_limits<int>::min()) {
                    insert = true;
                    right = nr[i];
                    break;
                }
            }
            if (!insert) {
                rows.emplace_back(nr[i], std::numeric_limits<int>::max(), std::numeric_limits<int>::min());
            }
        }

        return rows;
    }

    unsigned long long calculate(const std::vector<row>& rows) {
        std::string sol;
        for (const auto& row : rows) {
            sol += std::to_string(row.number);
        }

        return std::stoull(sol);
    }

    unsigned long long transformRow(const row& line) {
        std::string num;
        if (line.left != std::numeric_limits<int>::max()) {
            num += std::to_string(line.left);
        }
        num += std::to_string(line.number);
        if (line.right != std::numeric_limits<int>::min()) {
            num += std::to_string(line.right);
        }
        return std::stoull(num);
    }

    unsigned long long part_1(std::string_view path) {
        std::string line = file::readFileAsString(path);
        std::vector<int> nr = utils::splitStringToInt(line, ":,");
        return calculate(solve(nr));
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        unsigned long long min = std::numeric_limits<unsigned long long>::max();
        unsigned long long max = std::numeric_limits<unsigned long long>::min();
        for (const auto& line : lines) {
            std::vector<int> nr = utils::splitStringToInt(line, ":,");
            unsigned long long s = calculate(solve(nr));
            min = std::min(min, s);
            max = std::max(max, s);
        }
        return max - min;
    }

    unsigned long long part_3(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::pair<int, std::vector<row>>> rows;
        for (const auto& line : lines) {
            std::vector<int> nr = utils::splitStringToInt(line, ":,");
            rows.emplace_back(nr[0], solve(nr));
        }

        std::sort(rows.begin(), rows.end(), [](const std::pair<int, std::vector<row>>& a, const std::pair<int, std::vector<row>>& b) {
            if (calculate(a.second) != calculate(b.second)) {
                return calculate(a.second) > calculate(b.second);
            }

            for (int i = 0; i < a.second.size(); i++) {
                if (transformRow(a.second[i]) != transformRow(b.second[i])) {
                    return transformRow(a.second[i]) > transformRow(b.second[i]);
                }
            }
            return a.first > b.first;
        });

        unsigned long long sol = 0;
        for (int i = 0; i < rows.size(); i++) {
            sol += (i + 1) * rows[i].first;
        }

        return sol;
    }
}

#ifdef TESTING
namespace aoccodes_2025_day05 {
    TEST(Testscodes_2025Day05, part_1_test) {
        ASSERT_EQ(part_1("../codes_2025/day05/input/input_part_1_test.in"), 581078);
    }

    TEST(Testscodes_2025Day05, part_1_real_test) {
        ASSERT_EQ(part_1("../codes_2025/day05/input/input_part_1.in"), 2754578356);
    }

    TEST(Testscodes_2025Day05, part_2_test) {
        ASSERT_EQ(part_2("../codes_2025/day05/input/input_part_2_test.in"), 77053);
    }

    TEST(Testscodes_2025Day05, part_2_real_test) {
        ASSERT_EQ(part_2("../codes_2025/day05/input/input_part_2.in"), 8436060100176);
    }

    TEST(Testscodes_2025Day05, part_3_test) {
        ASSERT_EQ(part_3("../codes_2025/day05/input/input_part_3_test.in"), 260);
    }

    TEST(Testscodes_2025Day05, part_3_real_test) {
        ASSERT_EQ(part_3("../codes_2025/day05/input/input_part_3.in"), 31212509);
    }
}
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoccodes_2025_day05::part_1("../codes_2025/day05/input/input_part_1.in"));
    fmt::print("Part 2: {}\n", aoccodes_2025_day05::part_2("../codes_2025/day05/input/input_part_2.in"));
    fmt::print("Part 3: {}\n", aoccodes_2025_day05::part_3("../codes_2025/day05/input/input_part_3.in"));

    return 0;
}
#endif
