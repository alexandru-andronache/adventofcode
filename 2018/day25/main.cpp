#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2018_day25 {
    int manhattanDistance(std::tuple<int, int, int, int> p1, std::tuple<int, int, int, int> p2) {
        auto [x1, y1, z1, w1] = p1;
        auto [x2, y2, z2, w2] = p2;
        return std::abs(x1 - x2) + std::abs(y1 - y2) + std::abs(z1 - z2) + std::abs(w1 - w2);
    }

    int part_1(std::string_view path) {
        std::vector<std::tuple<int, int, int, int>> points;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " (,;:)");
            points.emplace_back(std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]));
        }

        std::vector<std::vector<std::tuple<int, int, int, int>>> constellations;

        for (const auto& p : points) {
            bool foundInAConstellation = false;
            std::vector<int> constellationIndex;

            for (int i = 0; i < constellations.size(); ++i) {
                bool found = false;
                for (const auto &c : constellations[i]) {
                    if (manhattanDistance(c, p) <= 3) {
                        found = true;
                    }
                }
                if (found) {
                    constellationIndex.push_back(i);
                    foundInAConstellation = true;
                }
            }
            if (!foundInAConstellation) {
                constellations.push_back({p});
            }
            else {
                constellations[constellationIndex[0]].push_back(p);
                for (int i = 1; i < constellationIndex.size(); ++i) {
                    constellations[constellationIndex[0]].insert(constellations[constellationIndex[0]].end(),
                                                                 constellations[constellationIndex[i]].begin(),
                                                                 constellations[constellationIndex[i]].end());
                }
                for (int i = 1; i < constellationIndex.size(); ++i) {
                    constellations.erase(constellations.begin() + constellationIndex[i] - i + 1);
                }
            }
        }

        return constellations.size();
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day25::part_1("../2018/day25/input.in") << std::endl;
    return 0;
}
#endif
