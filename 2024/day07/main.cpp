#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <stack>
#include <set>

namespace aoc2024_day07 {
    bool isSol = false;

    bool numberEndsWith(long long total, long long ends) {
        while (ends > 0 && total > 0) {
            if (total % 10 != ends % 10) {
                return false;
            }
            total = total / 10;
            ends = ends / 10;
        }
        return (ends == 0);
    }

    long long removeNumberFromEnd(long long total, long long ends) {
        while (ends > 0) {
            total = total / 10;
            ends = ends / 10;
        }
        return total;
    }

    void solve(long long total, const std::vector<long long>& numbers, int pos, bool withConcat) {
        if ((total == 0 && pos != -1) || isSol) {
            return;
        }
        if (pos == -1) {
            if (total == 0) {
                isSol = true;
            }
        }
        else {
            if (total - numbers[pos] >= 0) {
                solve(total - numbers[pos], numbers, pos - 1, withConcat);
            }
            if (numberEndsWith(total, numbers[pos]) && withConcat) {
                solve(removeNumberFromEnd(total, numbers[pos]), numbers, pos - 1, withConcat);
            }
            if (total % numbers[pos] == 0) {
                solve(total / numbers[pos], numbers, pos - 1, withConcat);
            }
        }
    }

    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sum = 0;
        for (const auto& line : input) {
            std::vector<long long> tokens = utils::splitStringToLL(line, ": ");
            isSol = false;
            solve(tokens[0], {tokens.begin() + 1, tokens.end()}, tokens.size() - 2, false);
            sum += isSol * tokens[0];
        }
        return sum;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sum = 0;
        for (const auto& line : input) {
            std::vector<long long> tokens = utils::splitStringToLL(line, ": ");
            isSol = false;
            solve(tokens[0], {tokens.begin() + 1, tokens.end()}, tokens.size() - 2, true);
            sum += isSol * tokens[0];
        }
        return sum;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day07::part_1("../2024/day07/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day07::part_2("../2024/day07/input.in") << std::endl;

    return 0;
}
#endif
