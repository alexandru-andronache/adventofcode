#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2016_day15 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::pair<int, int>> discs;
        for (const auto& line : input) {
            std::vector<std::string> s = utils::splitString(line, " .");
            discs.emplace_back(std::stoi(s[3]), std::stoi(s[11]));
        }

        int time = 0;
        while (true) {
            bool sol = true;
            for (int i = 0; i < discs.size(); ++i) {
                int pos = (discs[i].second + time + i + 1) % discs[i].first;
                if (pos != 0) sol = false;
            }
            if (sol) {
                return time;
            }
            time++;
        }
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::pair<int, int>> discs;
        for (const auto& line : input) {
            std::vector<std::string> s = utils::splitString(line, " .");
            discs.emplace_back(std::stoi(s[3]), std::stoi(s[11]));
        }

        discs.emplace_back(11, 0);
        int time = 0;
        while (true) {
            bool sol = true;
            for (int i = 0; i < discs.size(); ++i) {
                int pos = (discs[i].second + time + i + 1) % discs[i].first;
                if (pos != 0) sol = false;
            }
            if (sol) {
                return time;
            }
            time++;
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day15::part_1("../2016/day15/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2016_day15::part_2("../2016/day15/input.in") << std::endl;

    return 0;
}
#endif
