#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <string>
#include <map>

namespace aoc2022_day02 {
    const int ROCK = 1;
    const int PAPER = 2;
    const int SCISSORS = 3;
    const int LOST = 0;
    const int DRAW = 3;
    const int WIN = 6;
    std::map<std::string, int> shapes {{"A", ROCK}, {"B", PAPER}, {"C", SCISSORS},
                                       {"X", ROCK}, {"Y", PAPER}, {"Z", SCISSORS}};
    std::map<std::string, int> results{{"X", LOST}, {"Y", DRAW}, {"Z", WIN}};

    std::map<std::pair<std::string, std::string>, int> outcome_part_1 {{{"A", "X"}, DRAW},
                                                                       {{"A", "Y"}, WIN},
                                                                       {{"A", "Z"}, LOST},
                                                                       {{"B", "X"}, LOST},
                                                                       {{"B", "Y"}, DRAW},
                                                                       {{"B", "Z"}, WIN},
                                                                       {{"C", "X"}, WIN},
                                                                       {{"C", "Y"}, LOST},
                                                                       {{"C", "Z"}, DRAW}};

    std::map<std::pair<std::string, int>, std::string> outcome_part_2 {{{"A", DRAW}, "X"},
                                                                       {{"A", LOST}, "Z"},
                                                                       {{"A", WIN}, "Y"},
                                                                       {{"B", DRAW}, "Y"},
                                                                       {{"B", LOST}, "X"},
                                                                       {{"B", WIN}, "Z"},
                                                                       {{"C", DRAW}, "Z"},
                                                                       {{"C", LOST}, "Y"},
                                                                       {{"C", WIN}, "X"}};

    int part_1(std::string_view path) {
        int sol = 0;
        std::vector<std::string> input = file::readFileAsArrayString(path);
        for (const auto& line : input) {
            std::vector<std::string> tokens = utils::splitString(line, " ");
            sol += outcome_part_1[{tokens[0], tokens[1]}] + shapes[tokens[1]];
        }
        return sol;
    }

    int part_2(std::string_view path) {
        int sol = 0;
        std::vector<std::string> input = file::readFileAsArrayString(path);
        for (const auto& line : input) {
            std::vector<std::string> tokens = utils::splitString(line, " ");

            sol += results[tokens[1]] + shapes[outcome_part_2[{tokens[0], results[tokens[1]]}]];
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day02::part_1("../2022/day02/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day02::part_2("../2022/day02/input.in") << std::endl;

    return 0;
}
#endif
