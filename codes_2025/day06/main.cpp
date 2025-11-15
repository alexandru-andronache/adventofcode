#include "file.h"
#include "utilities.h"
#include <algorithm>
#include <ranges>
#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoccodes_2025_day06 {
    unsigned long long part_1(std::string_view path) {
        std::string line = file::readFileAsString(path);
        int uppercase = 0;
        int sol = 0;
        for (const auto& c : line) {
            if (c == 'A') {
                uppercase++;
            }
            else if (c == 'a') {
                sol += uppercase;
            }
        }
        return sol;
    }

    unsigned long long part_2(std::string_view path) {
        std::string line = file::readFileAsString(path);
        std::array<int, 'Z' - 'A' + 1> uppercase{};
        int sol = 0;
        for (const auto& c : line) {
            if (c >= 'A' && c <= 'Z') {
                uppercase[c - 'A']++;
            }
            else if (c >= 'a' && c <= 'z') {
                sol += uppercase[c - 'a'];
            }
        }
        return sol;
    }

    struct count{
        std::array<int, 3> letters;
    };

    int countCharactersWithoutLeft(const std::vector<count>& counts, char c, int position, int distance) {
        // left
        int left = counts[position + 1].letters[c - 'a'] - counts[std::max(position - distance, 0)].letters[c - 'a'];
        int right = 0;
        if (position + distance + 1 < counts.size()) {
            right = counts[position + distance + 1].letters[c - 'a'] - counts[position + 1].letters[c - 'a'];
        }
        else {
            right = counts.back().letters[c - 'a'] - counts[position + 1].letters[c - 'a'];
            right += counts[position + distance + 2 - counts.size()].letters[c - 'a'];
        }
        return left + right;
    }

    int countCharacters(const std::vector<count>& counts, char c, int position, int distance) {
        int left = 0;
        if (position - distance >= 0) {
            left = counts[position + 1].letters[c - 'a'] - counts[position - distance].letters[c - 'a'];
        }
        else {
            left = counts[position + 1].letters[c - 'a'] - counts[0].letters[c - 'a'];
            left += counts.back().letters[c - 'a'] - counts[counts.size() - 1 - distance + position].letters[c - 'a'];
        }
        int right = 0;
        if (position + distance + 1 < counts.size()) {
            right = counts[position + distance + 1].letters[c - 'a'] - counts[position + 1].letters[c - 'a'];
        }
        else {
            right = counts.back().letters[c - 'a'] - counts[position + 1].letters[c - 'a'];
            right += counts[position + distance + 2 - counts.size()].letters[c - 'a'];
        }
        return left + right;
    }

    int countCharactersWithoutRight(const std::vector<count>& counts, char c, int position, int distance) {
        // left
        int left = 0;
        if (position - distance >= 0) {
            left = counts[position + 1].letters[c - 'a'] - counts[position - distance].letters[c - 'a'];
        }
        else {
            left = counts[position + 1].letters[c - 'a'] - counts[0].letters[c - 'a'];
            left += counts.back().letters[c - 'a'] - counts[counts.size() - 1 - distance + position].letters[c - 'a'];
        }
        int right = counts[std::min(position + 1 + distance, (int)counts.size() - 1)].letters[c - 'a'] - counts[position + 1].letters[c - 'a'];
        return left + right;
    }

    unsigned long long part_3(std::string_view path, int repeat = 1000, int distance = 1000) {
        std::string line = file::readFileAsString(path);
        std::vector<count> counts;
        count current{};
        counts.push_back(current);
        for (const auto& c : line) {
            if (c == 'A') current.letters[0]++;
            if (c == 'B') current.letters[1]++;
            if (c == 'C') current.letters[2]++;
            counts.emplace_back(current);
        }

        unsigned long long sol = 0;
        for (int i = 0; i < line.size(); i++) {
            if (line[i] >= 'a' && line[i] <= 'c') {
                sol += countCharactersWithoutLeft(counts, line[i], i, distance);
            }
        }
        for (int i = 0; i < line.size(); i++) {
            if (line[i] >= 'a' && line[i] <= 'c') {
                sol += countCharacters(counts, line[i], i, distance) * (repeat - 2);
            }
        }
        for (int i = 0; i < line.size(); i++) {
            if (line[i] >= 'a' && line[i] <= 'c') {
                sol += countCharactersWithoutRight(counts, line[i], i, distance);
            }
        }

        return sol;
    }
}

#ifdef TESTING
namespace aoccodes_2025_day06 {
    TEST(Testscodes_2025Day06, part_1_test) {
        ASSERT_EQ(part_1("../codes_2025/day06/input/input_part_1_test.in"), 5);
    }

    TEST(Testscodes_2025Day06, part_1_real_test) {
        ASSERT_EQ(part_1("../codes_2025/day06/input/input_part_1.in"), 143);
    }

    TEST(Testscodes_2025Day06, part_2_test) {
        ASSERT_EQ(part_2("../codes_2025/day06/input/input_part_2_test.in"), 11);
    }

    TEST(Testscodes_2025Day06, part_2_real_test) {
        ASSERT_EQ(part_2("../codes_2025/day06/input/input_part_2.in"), 3780);
    }

    TEST(Testscodes_2025Day06, part_3_test) {
        ASSERT_EQ(part_3("../codes_2025/day06/input/input_part_3_test.in", 2, 10), 72);
    }

    // TEST(Testscodes_2025Day06, part_3_test_2) {
    //     ASSERT_EQ(part_3("../codes_2025/day06/input/input_part_3_test.in", 1000, 1000), 3442321);
    // }

    TEST(Testscodes_2025Day06, part_3_real_test) {
        ASSERT_EQ(part_3("../codes_2025/day06/input/input_part_3.in"), 1666826546);
    }
}
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoccodes_2025_day06::part_1("../codes_2025/day06/input/input_part_1.in"));
    fmt::print("Part 2: {}\n", aoccodes_2025_day06::part_2("../codes_2025/day06/input/input_part_2.in"));
    fmt::print("Part 3: {}\n", aoccodes_2025_day06::part_3("../codes_2025/day06/input/input_part_3.in"));

    return 0;
}
#endif
