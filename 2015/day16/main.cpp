#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2015_day16 {
    int part_1(std::string_view path, const std::vector<std::pair<std::string, int>>& sue) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        for (const auto& line : input) {
            std::vector<std::string> tokens = utils::splitString(line, " :,");
            int found = true;
            for (int j = 2; j <= 6; j += 2) {
                for (const auto& type : sue) {
                    if (tokens[j] == type.first && std::stoi(tokens[j + 1]) != type.second) {
                        found = false;
                    }
                }
            }
            if (found) {
                return std::stoi(tokens[1]);
            }
        }
        return 0;
    }

    int part_2(std::string_view path, const std::vector<std::pair<std::string, int>>& sue) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        for (const auto& line : input) {
            std::vector<std::string> tokens = utils::splitString(line, " :,");
            int found = true;
            for (int j = 2; j <= 6; j += 2) {
                for (const auto& type : sue) {
                    if (tokens[j] == "cats" || tokens[j] == "trees") {
                        if (tokens[j] == type.first && std::stoi(tokens[j + 1]) <= type.second) {
                            found = false;
                        }
                    }
                    else if (tokens[j] == "pomeranians" || tokens[j] == "goldfish") {
                        if (tokens[j] == type.first && std::stoi(tokens[j + 1]) >= type.second) {
                            found = false;
                        }
                    }
                    else if (tokens[j] == type.first && std::stoi(tokens[j + 1]) != type.second) {
                        found = false;
                    }
                }
            }
            if (found) {
                return std::stoi(tokens[1]);
            }
        }
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2015_day16::part_1("../2015/day16/input.in",{{"children", 3},
                                                                               {"cats", 7},
                                                                               {"samoyeds", 2},
                                                                               {"pomeranians", 3},
                                                                               {"akitas", 0},
                                                                               {"vizslas", 0},
                                                                               {"goldfish", 5},
                                                                               {"trees", 3},
                                                                               {"cars", 2},
                                                                               {"perfumes", 1}}) << std::endl;
    std::cout << "Part 2: " << aoc2015_day16::part_2("../2015/day16/input.in", {{"children", 3},
                                                                                {"cats", 7},
                                                                                {"samoyeds", 2},
                                                                                {"pomeranians", 3},
                                                                                {"akitas", 0},
                                                                                {"vizslas", 0},
                                                                                {"goldfish", 5},
                                                                                {"trees", 3},
                                                                                {"cars", 2},
                                                                                {"perfumes", 1}}) << std::endl;

    return 0;
}
#endif
