#include "file.h"
#include "utilities.h"
#include <iostream>
#include <optional>
#include <numeric>

namespace aoc2021_day22 {

    struct cube {
        cube () = default;
        cube(bool t, int64_t a, int64_t b, int64_t c, int64_t d, int64_t e, int64_t f) {
            type = t;
            x1 = a;
            x2 = b;
            y1 = c;
            y2 = d;
            z1 = e;
            z2 = f;
        }
        bool type;
        int64_t x1;
        int64_t x2;
        int64_t y1;
        int64_t y2;
        int64_t z1;
        int64_t z2;
    };

    std::optional<cube> intersection(const cube& cube1, const cube& cube2) {
        cube c;
        if (cube1.x1 >= cube2.x1 && cube1.x1 <= cube2.x2) {
            c.x1 = cube1.x1;
            c.x2 = std::min(cube1.x2, cube2.x2);
        }
        else if (cube2.x1 >= cube1.x1 && cube2.x1 <= cube1.x2) {
            c.x1 = cube2.x1;
            c.x2 = std::min(cube1.x2, cube2.x2);
        }
        else {
            return std::nullopt;
        }

        if (cube1.y1 >= cube2.y1 && cube1.y1 <= cube2.y2) {
            c.y1 = cube1.y1;
            c.y2 = std::min(cube1.y2, cube2.y2);
        }
        else if (cube2.y1 >= cube1.y1 && cube2.y1 <= cube1.y2) {
            c.y1 = cube2.y1;
            c.y2 = std::min(cube1.y2, cube2.y2);
        }
        else {
            return std::nullopt;
        }

        if (cube1.z1 >= cube2.z1 && cube1.z1 <= cube2.z2) {
            c.z1 = cube1.z1;
            c.z2 = std::min(cube1.z2, cube2.z2);
        }
        else if (cube2.z1 >= cube1.z1 && cube2.z1 <= cube1.z2) {
            c.z1 = cube2.z1;
            c.z2 = std::min(cube1.z2, cube2.z2);
        }
        else {
            return std::nullopt;
        }
        return c;
    }

    int64_t calculateVolume(const std::vector<cube>& cubes) {
        return std::accumulate(cubes.begin(), cubes.end(), 0LL,[](int64_t sum, const auto& c) {
            if (c.type) {
                return sum + (c.x2 - c.x1 + 1) * (c.y2 - c.y1 + 1) * (c.z2 - c.z1 + 1);
            }
            return sum - (c.x2 - c.x1 + 1) * (c.y2 - c.y1 + 1) * (c.z2 - c.z1 + 1);
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
                    intersect.value().type = !c.type;
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
                    intersect.value().type = !c.type;
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
