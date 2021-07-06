#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <set>

namespace aoc2017_day04 {
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::vector<std::string>> input;

        for (const auto& line : lines) {
            input.push_back(utils::splitString(line, " "));
        }

        int sol = 0;
        for (const auto& line : input) {
            std::set<std::string> elements;
            for (const auto& s : line) {
                if (elements.find(s) == elements.end()) {
                    elements.insert(s);
                }
            }
            if (elements.size() == line.size()) {
                sol++;
            }
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::vector<std::string>> input;

        for (const auto& line : lines) {
            input.push_back(utils::splitString(line, " "));
        }

        int sol = 0;
        for (const auto& line : input) {
            std::vector<std::string> elements;
            for (const auto& s : line) {
                bool found = false;
                for (const auto& e : elements) {
                    found = found || utils::isAnagram(s, e);
                }
                if (!found) elements.push_back(s);
            }
            if (elements.size() == line.size()) {
                sol++;
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day04::part_1("../2017/day04/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day04::part_2("../2017/day04/input.in") << std::endl;

    return 0;
}
#endif
