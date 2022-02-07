#include "file.h"
#include <iostream>
#include <vector>
#include <algorithm>

namespace aoc2015_day05 {
    bool isNicePart1(std::string_view line) {
        int count = std::count(line.begin(), line.end(), 'a') +
                std::count(line.begin(), line.end(), 'e') +
                std::count(line.begin(), line.end(), 'i') +
                std::count(line.begin(), line.end(), 'o') +
                std::count(line.begin(), line.end(), 'u');
        bool isSimilar = false;
        for (int i = 1; i < line.size(); ++i) {
            if (line[i] == line[i - 1]) {
                isSimilar = true;
            }
        }
        bool containsBadStrings = (line.find("ab") != std::string::npos) ||
                (line.find("cd") != std::string::npos) ||
                (line.find("pq") != std::string::npos) ||
                (line.find("xy") != std::string::npos);

        return (count >= 3) && isSimilar && !containsBadStrings;
    }

    bool isNicePart2(std::string_view line) {
        bool foundPair = false;
        for (int i = 0; i < line.size() - 1; ++i) {
            foundPair = foundPair || (line.find(line.substr(i, 2), i + 2) != std::string::npos);
        }
        bool foundLetterRepeat = false;
        for (int i = 0; i < line.size() - 2; ++i) {
            foundLetterRepeat = foundLetterRepeat || (line[i] == line[i + 2]);
        }
        return foundPair && foundLetterRepeat;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int sol = 0;
        for (const auto& line : input) {
            sol += isNicePart1(line);
        }
        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int sol = 0;
        for (const auto& line : input) {
            sol += isNicePart2(line);
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day05::part_1("../2015/day05/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2015_day05::part_2("../2015/day05/input.in") << std::endl;

    return 0;
}
#endif
