#include "file.h"
#include <iostream>
#include <set>
#include <vector>

namespace aoc2015_day03 {
    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::set<std::pair<int, int>> visited;
        int houses = 1;
        int x = 0, y = 0;
        visited.insert({x, y});

        for (const auto& l : input) {
            y += (-1) * (l == '<') + (l == '>');
            x += (-1) * (l == '^') + (l == 'v');
            houses += (visited.count({x, y}) + 1) % 2;
            visited.insert({x, y});
        }

        return houses;
    }

    int part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::set<std::pair<int, int>> visited;
        int houses = 1;
        std::vector<std::pair<int, int>> position{{0, 0}, {0, 0}};
        visited.insert(position[0]);
        int index = 0;

        for (const auto& l : input) {
            position[index].second += (-1) * (l == '<') + (l == '>');
            position[index].first += (-1) * (l == '^') + (l == 'v');
            houses += (visited.count({position[index].first, position[index].second}) + 1) % 2;
            visited.insert({position[index].first, position[index].second});
            index = (index + 1) % position.size();
        }

        return houses;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day03::part_1("../2015/day03/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2015_day03::part_2("../2015/day03/input.in") << std::endl;

    return 0;
}
#endif
