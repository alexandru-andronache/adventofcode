#include "file.h"
#include <iostream>
#include <utilities.h>

namespace aoc2024_day05 {
    int part_1(std::string_view path) {
        int sol = 0;
        // std::string input = file::readFileAsString(path);
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::pair<int, int>> pages;
        int i = 0;
        while (input[i] != "") {
            std::vector<int> p = utils::splitStringToInt(input[i], "|");
            pages.emplace_back(p[0], p[1]);
            i++;
        }
        i++;
        while (i < input.size())
        {
            std::vector<int> p = utils::splitStringToInt(input[i], ",");
            bool found = true;
            for (int j = 0; j < p.size() - 1; ++j) {
                for (const auto& page : pages) {
                    if (p[j] == page.second && p[j + 1] == page.first) {
                        found = false;
                    }
                }
            }
            if (found) {
                sol += p[p.size() / 2];
            }
            i++;
        }

        return sol;
    }

    int part_2(std::string_view path) {
        int sol = 0;
        // std::string input = file::readFileAsString(path);
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::pair<int, int>> pages;
        int i = 0;
        while (input[i] != "") {
            std::vector<int> p = utils::splitStringToInt(input[i], "|");
            pages.emplace_back(p[0], p[1]);
            i++;
        }
        i++;
        while (i < input.size())
        {
            std::vector<int> p = utils::splitStringToInt(input[i], ",");
            bool found = true;
            for (int j = 0; j < p.size() - 1; ++j) {
                for (const auto& page : pages) {
                    if (p[j] == page.second && p[j + 1] == page.first) {
                        found = false;
                    }
                }
            }
            if (!found) {
                bool newFound = false;
                while (!newFound)
                {
                    newFound = true;
                    for (int j = 0; j < p.size() - 1; ++j) {
                        for (const auto& page : pages) {
                            if (p[j] == page.second && p[j + 1] == page.first) {
                                newFound = false;
                                std::swap(p[j], p[j + 1]);
                                break;
                            }
                        }
                    }
                }
                sol += p[p.size() / 2];
            }
            i++;
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day05::part_1("../2024/day05/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day05::part_2("../2024/day05/input.in") << std::endl;

    return 0;
}
#endif
