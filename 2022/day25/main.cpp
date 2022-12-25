#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>

namespace aoc2022_day25 {
    std::map<char, int> snafu{{'0', 0}, {'1', 1}, {'2', 2}, {'-', -1}, {'=', -2}};
    std::map<int, char> reverseSnafu {{0, '0'}, {1, '1'}, {2, '2'}, {3, '='}, {4, '-'}};

    unsigned long long toDecimal(std::string str) {
        unsigned long long nr = 0;
        unsigned long long power = 1;
        std::reverse(str.begin(), str.end());
        for (const auto& c : str) {
            nr = nr + power * snafu[c];
            power = power * 5;
        }
        return nr;
    }

    std::string toSnafu(unsigned long long nr) {
        std::string str;
        while (nr > 0) {
            int k = nr % 5;
            str += reverseSnafu[k];
            nr = (nr + ((k > 2) ? 5 - k : 0)) / 5;
        }
        std::reverse(str.begin(), str.end());
        return str;
    }

    std::string part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        unsigned long long sum = 0;
        for (const auto& l : lines) {
            sum += toDecimal(l);
        }
        return toSnafu(sum);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day25::part_1("../2022/day25/input.in") << std::endl;
    return 0;
}
#endif
