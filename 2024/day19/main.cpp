#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2024_day19 {
    bool isPossible = false;
    void test(std::string_view line, const std::vector<std::string>& words) {
        if (line.empty()) {
            isPossible = true;
        }
        if (isPossible) {
            return;
        }
        for (const auto& word : words) {
            if (line.starts_with(word)) {
                test(line.substr(word.size()), words);
            }
        }
    }

    std::map<std::string_view, unsigned long long> cache;
    unsigned long long count(std::string_view line, const std::vector<std::string>& words) {
        if (line.empty()) {
            return 1;
        }
        if (cache.contains(line)) {
            return cache[line];
        }
        unsigned long long nr = 0;
        for (const auto& word : words) {
            if (line.starts_with(word)) {
                nr += count(line.substr(word.size()), words);
            }
        }
        cache[line] = nr;
        return nr;
    }
    int part_1(std::string_view path) {
        int count = 0;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::string> words = utils::splitString(lines[0], ", ");
        for (int i = 2; i < lines.size(); ++i) {
            isPossible = false;
            test(lines[i], words);
            count += isPossible;
        }
        return count;
    }

    unsigned long long part_2(std::string_view path) {
        unsigned long long sol = 0;
        cache.clear();
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::string> words = utils::splitString(lines[0], ", ");
        for (int i = 2; i < lines.size(); ++i) {
            sol += count(lines[i], words);
        }
        return sol;
    }
}

#ifdef TESTING
namespace aoc2024_day19 {
    TEST(Tests2024Day19, part_1_test) {
        ASSERT_EQ(part_1("../2024/day19/input_test.in"), 6);
    }

    TEST(Tests2024Day19, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day19/input.in"), 236);
    }

    TEST(Tests2024Day19, part_2_test) {
        ASSERT_EQ(part_2("../2024/day19/input_test.in"), 16);
    }

    TEST(Tests2024Day19, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day19/input.in"), 643685981770598);
    }
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day19::part_1("../2024/day19/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day19::part_2("../2024/day19/input.in") << std::endl;

    return 0;
}
#endif
