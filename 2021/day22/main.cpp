#include "file.h"
#include "utilities.h"
#include <iostream>
#include <optional>
#include <numeric>
#include <array>

namespace aoc2021_day22 {

    struct cube {
        cube () = default;
        cube(bool t, int64_t x1, int64_t x2, int64_t y1, int64_t y2, int64_t z1, int64_t z2) {
            type = t;
            vertex[0] = {x1, x2};
            vertex[1] = {y1, y2};
            vertex[2] = {z1, z2};
        }
        bool type;
        std::array<std::pair<int64_t, int64_t>, 3> vertex;
    };

    std::optional<cube> intersection(const cube& cube1, const cube& cube2) {
        cube c;
        for (int i = 0; i < cube1.vertex.size(); ++i) {
            if (cube1.vertex[i].first >= cube2.vertex[i].first && cube1.vertex[i].first <= cube2.vertex[i].second) {
                c.vertex[i].first = cube1.vertex[i].first;
                c.vertex[i].second = std::min(cube1.vertex[i].second, cube2.vertex[i].second);
            }
            else if (cube2.vertex[i].first >= cube1.vertex[i].first && cube2.vertex[i].first <= cube1.vertex[i].second) {
                c.vertex[i].first = cube2.vertex[i].first;
                c.vertex[i].second = std::min(cube1.vertex[i].second, cube2.vertex[i].second);
            }
            else {
                return std::nullopt;
            }
        }
        c.type = !cube1.type;
        return c;
    }

    int64_t calculateVolume(const std::vector<cube>& cubes) {
        return std::accumulate(cubes.begin(), cubes.end(), 0LL,[](int64_t sum, const auto& c) {
            int64_t volume = std::accumulate(c.vertex.begin(), c.vertex.end(), 1LL, [](int64_t v, const auto& vertex) {
                return v * (vertex.second - vertex.first + 1);
            });
            if (c.type) {
                return sum + volume;
            }
            return sum - volume;
        });
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<cube> cubes;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " =,.");
            if (!(std::atoi(tokens[2].c_str()) >= -50 && std::atoi(tokens[2].c_str()) <= 50 &&
                std::atoi(tokens[3].c_str()) >= -50 && std::atoi(tokens[3].c_str()) <= 50 &&
                std::atoi(tokens[5].c_str()) >= -50 && std::atoi(tokens[5].c_str()) <= 50 &&
                std::atoi(tokens[6].c_str()) >= -50 && std::atoi(tokens[6].c_str()) <= 50 &&
                std::atoi(tokens[8].c_str()) >= -50 && std::atoi(tokens[8].c_str()) <= 50 &&
                std::atoi(tokens[9].c_str()) >= -50 && std::atoi(tokens[9].c_str()) <= 50)) {
                continue;
            }

            cube activeCube(tokens[0] == "on",
                            std::atoi(tokens[2].c_str()),
                            std::atoi(tokens[3].c_str()),
                            std::atoi(tokens[5].c_str()),
                            std::atoi(tokens[6].c_str()),
                            std::atoi(tokens[8].c_str()),
                            std::atoi(tokens[9].c_str()));

            std::vector<cube> newCubes;
            for (const auto& c : cubes) {
                std::optional<cube> intersect = intersection(c, activeCube);
                if (intersect.has_value()) {
                    newCubes.push_back(intersect.value());
                }
            }
            cubes.insert(cubes.end(), newCubes.begin(), newCubes.end());
            if (activeCube.type) {
                cubes.emplace_back(activeCube);
            }
        }

        return calculateVolume(cubes);
    }

    int64_t part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<cube> cubes;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " =,.");

            cube activeCube(tokens[0] == "on",
                            std::atoi(tokens[2].c_str()),
                            std::atoi(tokens[3].c_str()),
                            std::atoi(tokens[5].c_str()),
                            std::atoi(tokens[6].c_str()),
                            std::atoi(tokens[8].c_str()),
                            std::atoi(tokens[9].c_str()));

            std::vector<cube> newCubes;

            for (const auto& c : cubes) {
                std::optional<cube> intersect = intersection(c, activeCube);
                if (intersect.has_value()) {
                    newCubes.push_back(intersect.value());
                }
            }
            cubes.insert(cubes.end(), newCubes.begin(), newCubes.end());
            if (activeCube.type) {
                cubes.emplace_back(activeCube);
            }
        }

        return calculateVolume(cubes);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day22::part_1("../2021/day22/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day22::part_2("../2021/day22/input.in") << std::endl;

    return 0;
}
#endif
