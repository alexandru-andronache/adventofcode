#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>

namespace aoc2020_day02 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int sol = 0;
        for (const auto &line : input) {
            std::vector<std::string> words = utils::splitString(line, "- :");
            int start = atoi(words[0].c_str());
            int end = atoi(words[1].c_str());
            int nr = std::count(words[3].begin(), words[3].end(), words[2][0]);
            if (nr >= start && nr <= end) {
                sol++;
            }
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int sol = 0;
        for (const auto &line : input) {
            std::vector<std::string> words = utils::splitString(line, "- :");
            int first = atoi(words[0].c_str()) - 1;
            int second = atoi(words[1].c_str()) - 1;
            if ((words[3][first] == words[2][0]) + (words[3][second] == words[2][0]) == 1) {
                sol++;
            }
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day02::part_1("../2020/day02/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day02::part_2("../2020/day02/input.in") << std::endl;

    return 0;
}
#endif
