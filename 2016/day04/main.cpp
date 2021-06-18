#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2016_day04 {
    int part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<std::string>> lines;
        for (const auto& line : input) {
            lines.push_back(utils::splitString(line, "-[]"));
        }

        int sum = 0;
        for (const auto& line : lines) {
            std::vector<std::pair<char, int>> letters(26);
            for (int i = 0; i < 26; ++i) {
                letters[i] = {i + 'a', 0};
            }
            for (int i = 0; i < line.size() - 2; ++i) {
                for (const auto& c : line[i]) {
                    letters[c - 'a'].second++;
                }
            }
            std::sort(letters.begin(), letters.end(), [](auto a, auto b) {
                if (a.second != b.second) {
                    return a.second > b.second;
                }
                return a.first < b.first;
            });

            bool isSol = true;
            for (int i = 0; i < line.back().size(); ++i) {
                if (line.back()[i] != letters[i].first) {
                    isSol = false;
                }
            }
            if (isSol) {
                sum += atoi(line.end()[-2].c_str());
            }
        }
        return sum;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::vector<std::string>> lines;
        for (const auto& line : input) {
            lines.push_back(utils::splitString(line, "-[]"));
        }

        for (const auto& line : lines) {
            int id = atoi(line.end()[-2].c_str());
            std::string newLine;
            for (const auto& word : line) {
                for (const auto& c : word) {
                    char x = (c - 'a' + id) % 26 + 'a';
                    newLine += x;
                }
                if (newLine == "northpole") {
                    return id;
                }
                newLine += ' ';
            }
        }
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day04::part_1("../2016/day04/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2016_day04::part_2("../2016/day04/input.in") << std::endl;

    return 0;
}
#endif
