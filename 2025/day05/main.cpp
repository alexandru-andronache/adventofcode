#include "file.h"
#include "utilities.h"
#include <vector>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day05 {
    int part_1(std::string_view path) {
        // std::string input = file::readFileAsString(path);
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int result = 0;

        std::vector<std::pair<unsigned long long, unsigned long long>> ranges;

        int index = 0;
        while (!lines[index].empty()) {
            std::vector<std::string> tokens = utils::splitString(lines[index], "-");
            unsigned long long start = std::stoull(tokens[0]);
            unsigned long long end = std::stoull(tokens[1]);
            ranges.push_back({start, end});
            index++;
        }
        index++;
        for (int i = index; i < lines.size(); ++i) {
            unsigned long long x = std::stoull(lines[i]);

            for (const auto& range : ranges) {
                if (x >= range.first && x <= range.second) {
                    result++;
                    break;
                }
            }
        }

        return result;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        unsigned long long result = 0;

        std::vector<std::pair<unsigned long long, unsigned long long>> ranges;

        int index = 0;
        while (!lines[index].empty()) {
            std::vector<std::string> tokens = utils::splitString(lines[index], "-");
            unsigned long long start = std::stoull(tokens[0]);
            unsigned long long end = std::stoull(tokens[1]);
            ranges.push_back({start, end});
            index++;
        }

        std::vector<std::pair<unsigned long long, unsigned long long>> final;

        for (const auto& range : ranges) {
            bool found = false;
            for (int i = 0; i < final.size(); ++i) {
                if (range.first >= final[i].first && range.second <= final[i].second) {
                    found = true;
                    break;
                }
                if (range.first <= final[i].first && range.second <= final[i].second && range.second >= final[i].first) {
                    final[i].first = range.first;
                    found = true;
                    break;
                }
                if (range.first >= final[i].first && range.first <= final[i].second && range.second >= final[i].second) {
                    final[i].second = range.second;
                    found = true;
                    break;
                }
                if (range.first <= final[i].second && range.second >= final[i].second) {
                    final[i].first = range.first;
                    final[i].second = range.second;
                    found = true;
                    break;
                }
            }
            if (!found) {
                final.push_back(range);
            }
        }

        bool f = true;
        while (f) {
            f = false;
            std::vector<std::pair<unsigned long long, unsigned long long>> final2;

            for (const auto& range : final) {
                bool found = false;
                for (int i = 0; i < final2.size(); ++i) {
                    if (range.first >= final2[i].first && range.second <= final2[i].second) {
                        f = true;
                        found = true;
                        break;
                    }
                    if (range.first <= final2[i].first && range.second <= final2[i].second && range.second >= final2[i].first) {
                        final2[i].first = range.first;
                        f = true;
                        found = true;
                        break;
                    }
                    if (range.first >= final2[i].first && range.first <= final2[i].second && range.second >= final2[i].second) {
                        final2[i].second = range.second;
                        f = true;
                        found = true;
                        break;
                    }
                    if (range.first <= final2[i].second && range.second >= final2[i].second) {
                        final2[i].first = range.first;
                        final2[i].second = range.second;
                        f = true;
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    final2.push_back(range);
                }
            }
            final = final2;
        }

        for (const auto& range : final) {
            result += (range.second - range.first + 1);
        }

        return result;
    }
}

#ifdef TESTING
    TEST(Test2025Day05, part_1_test) {
        ASSERT_EQ(aoc2025_day05::part_1("../2025/day05/input_test.in"), 3);
    }

    TEST(Test2025Day05, part_1_real_test) {
        ASSERT_EQ(aoc2025_day05::part_1("../2025/day05/input.in"), 862);
    }

    TEST(Test2025Day05, part_2_test) {
        ASSERT_EQ(aoc2025_day05::part_2("../2025/day05/input_test.in"), 14);
    }

    TEST(Test2025Day05, part_2_real_test) {
        ASSERT_EQ(aoc2025_day05::part_2("../2025/day05/input.in"), 357907198933892);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day05::part_1("../2025/day05/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day05::part_2("../2025/day05/input.in"));

    return 0;
}
#endif
