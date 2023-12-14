#include "file.h"
#include "utilities.h"
#include <iostream>
#include <numeric>
#include <map>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day14 {
    unsigned long long calculate(const std::vector<std::string>& input) {
        unsigned long long s = 0;

        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                if (input[i][j] == 'O') {
                    s += input.size() - i;
                }
            }
        }

        return s;
    }

    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        bool x = true;
        while (x) {
            x = false;
            for (int i = input.size() - 1; i > 0; --i) {
                for (int j = 0; j < input[0].size(); ++j) {
                    if ((input[i][j] == 'O') && (input[i - 1][j] == '.')) {
                        input[i - 1][j] = 'O';
                        input[i][j] = '.';
                        x = true;
                    }
                }
            }
        }

        return calculate(input);
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<std::vector<std::string>, int> prev;
        prev[input] = 0;
        int start = 0;
        int length = 0;

        bool found = false;
        for (int cycle = 0; cycle < 1000000000 && !found; ++cycle) {
            bool x = true;
            while (x) {
                x = false;
                for (int i = input.size() - 1; i > 0; --i) {
                    for (int j = 0; j < input[0].size(); ++j) {
                        if ((input[i][j] == 'O') && (input[i - 1][j] == '.')) {
                            input[i - 1][j] = 'O';
                            input[i][j] = '.';
                            x = true;
                        }
                    }
                }
            }

            //west
            x = true;
            while (x) {
                x = false;
                for (int i = 0; i < input.size(); ++i) {
                    for (int j = input[0].size() - 1; j > 0; --j) {
                        if ((input[i][j] == 'O') && (input[i][j - 1] == '.')) {
                            input[i][j - 1] = 'O';
                            input[i][j] = '.';
                            x = true;
                        }
                    }
                }
            }

            //south
            x = true;
            while (x) {
                x = false;
                for (int i = 0; i < input.size() - 1; ++i) {
                    for (int j = 0; j < input[0].size(); ++j) {
                        if ((input[i][j] == 'O') && (input[i + 1][j] == '.')) {
                            input[i + 1][j] = 'O';
                            input[i][j] = '.';
                            x = true;
                        }
                    }
                }
            }

            //east
            x = true;
            while (x) {
                x = false;
                for (int i = 0; i < input.size(); ++i) {
                    for (int j = 0; j < input[0].size() - 1; ++j) {
                        if ((input[i][j] == 'O') && (input[i][j + 1] == '.')) {
                            input[i][j + 1] = 'O';
                            input[i][j] = '.';
                            x = true;
                        }
                    }
                }
            }

            if (prev.contains(input)) {
                start = prev[input];
                length = cycle - start;
                found = true;
            }
            else {
                prev[input] = cycle;
            }
        }

        int end = (1000000000 - start) % length + start - 1;

        for (const auto& p : prev) {
            if (p.second == end) {
                return calculate(p.first);
            }
        }

        return 0;
    }
}

#ifdef TESTING
TEST(Tests2023Day14, part_1_test) {
    ASSERT_EQ(aoc2023_day14::part_1("../2023/day14/input_test.in"), 136);
}

TEST(Tests2023Day14, part_1_real_test) {
    ASSERT_EQ(aoc2023_day14::part_1("../2023/day14/input.in"), 108889);
}

TEST(Tests2023Day14, part_2_test) {
    ASSERT_EQ(aoc2023_day14::part_2("../2023/day14/input_test.in"), 64);
}

TEST(Tests2023Day14, part_2_real_test) {
    ASSERT_EQ(aoc2023_day14::part_2("../2023/day14/input.in"), 104671);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day14::part_1("../2023/day14/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2023_day14::part_2("../2023/day14/input.in") << std::endl;

    return 0;
}
#endif
