#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>

namespace aoc2015_day12 {
    int solve(std::string_view str, int& pos) {
        int sum = 0;
        bool isRed = false;
        std::string red = ":\"red\"";
        while (pos < str.size()) {
            if (str[pos] == '{') {
                pos++;
                sum += solve(str, pos);
            }
            else if (str[pos] == '}') {
                pos++;
                return sum * (!isRed);
            }
            else if ((pos + red.size() < str.size()) && str.substr(pos, red.size()) == red) {
                pos += red.size();
                isRed = true;
            }
            else {
                int prev = pos;
                sum += utils::getNumber(str, pos);
                pos += (prev == pos);
            }
        }
        return sum * (!isRed);
    }

    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        int sum = 0;
        int index = 0;
        while (index < input.size()) {
            sum += utils::getNumber(input, index);
            index++;
        }
        return sum;
    }

    int part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);
        int pos = 0;
        return solve(input, pos);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day12::part_1("../2015/day12/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2015_day12::part_2("../2015/day12/input.in") << std::endl;

    return 0;
}
#endif
