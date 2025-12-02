#include "file.h"
#include "utilities.h"
#include <vector>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day02 {
    unsigned long long part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        unsigned long long result = 0;

        std::vector<std::string> tokens = utils::splitString(input, "-,");

        for (int i = 0; i < tokens.size(); i += 2) {
            unsigned long long s = std::stoull(tokens[i]);
            unsigned long long e = std::stoull(tokens[i + 1]);
            for (unsigned long long v = s; v <= e; ++v) {
                std::vector<int> nr;
                unsigned long long c = v;
                while (c > 0) {
                    nr.push_back(c % 10);
                    c /= 10;
                }
                if (nr.size() % 2 == 0) {
                    int m = nr.size() / 2;
                    bool valid = true;
                    for (int j = 0; j < m; ++j) {
                        if (nr[j] != nr[m + j]) {
                            valid = false;
                        }
                    }
                    if (valid) {
                        result += v;
                    }
                }
            }
        }

        return result;
    }

    unsigned long long part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);
        unsigned long long result = 0;
        std::map<unsigned long long, bool> prev;

        std::vector<std::string> tokens = utils::splitString(input, "-,");

        for (int i = 0; i < tokens.size(); i += 2) {
            unsigned long long s = std::stoull(tokens[i]);
            unsigned long long e = std::stoull(tokens[i + 1]);
            for (unsigned long long v = s; v <= e; ++v) {
                // if (prev.contains(v)) {
                //     if (prev[v]) {
                //         result += v;
                //     }
                //     break;
                // }
                std::vector<int> nr;
                unsigned long long c = v;
                while (c > 0) {
                    nr.push_back(c % 10);
                    c /= 10;
                }
                for (int k = 1; k <= nr.size() / 2; ++k) {
                    bool valid = true;
                    if (nr.size() % k == 0) {
                        for (int j = 0; j < k && valid; ++j) {
                            for (int l = 1; l < nr.size() / k && valid; ++l) {
                                if (nr[j] != nr[j + l * k]) {
                                    valid = false;
                                }
                            }
                        }
                        if (valid) {
                            result += v;
                            // prev.insert({v, true});
                            break;
                        }
                    }
                }
                // prev.insert({v, false});
            }
        }

        return result;
    }
}

#ifdef TESTING
    TEST(Test2025Day02, part_1_test) {
        ASSERT_EQ(aoc2025_day02::part_1("../2025/day02/input_test.in"), 1227775554);
    }

    TEST(Test2025Day02, part_1_real_test) {
        ASSERT_EQ(aoc2025_day02::part_1("../2025/day02/input.in"), 13108371860);
    }

    TEST(Test2025Day02, part_2_test) {
        ASSERT_EQ(aoc2025_day02::part_2("../2025/day02/input_test.in"), 4174379265);
    }

    TEST(Test2025Day02, part_2_real_test) {
        ASSERT_EQ(aoc2025_day02::part_2("../2025/day02/input.in"), 22471660255);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day02::part_1("../2025/day02/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day02::part_2("../2025/day02/input.in"));

    return 0;
}
#endif
