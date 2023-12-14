#include "file.h"
#include "utilities.h"
#include <iostream>
#include <numeric>
#include <map>

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
        unsigned long long sol = 0;

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
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day14::part_1("../2023/day14/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2023_day14::part_2("../2023/day14/input.in") << std::endl;

    return 0;
}
#endif
