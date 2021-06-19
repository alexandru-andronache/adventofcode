#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2016_day06 {
    std::string part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        std::string sol;
        std::vector<std::vector<int>> chars(lines[0].size(), std::vector<int>(26, 0));
        for (const auto& line : lines) {
            for (int i = 0; i < line.size(); ++i) {
                chars[i][line[i] - 'a']++;
            }
        }

        for (const auto& column : chars) {
            auto it = std::max_element(column.begin(), column.end()) - column.begin();
            sol += (it + 'a');
        }
        return sol;
    }

    std::string part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        std::string sol;
        std::vector<std::vector<int>> chars(lines[0].size(), std::vector<int>(26, std::numeric_limits<int>::max()));
        for (const auto& line : lines) {
            for (int i = 0; i < line.size(); ++i) {
                chars[i][line[i] - 'a']++;
            }
        }

        for (const auto& column : chars) {
            auto it = std::min_element(column.begin(), column.end()) - column.begin();
            sol += (it + 'a');
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day06::part_1("../2016/day06/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day06::part_2("../2016/day06/input.in") << std::endl;

    return 0;
}
#endif
