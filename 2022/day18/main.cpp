#include "file.h"
#include "utilities.h"
#include <iostream>
#include <numeric>
#include <array>

namespace aoc2022_day18 {
    struct cube {
        std::array<int, 3> pos;
    };
    int countSides(std::string_view path) {
        std::vector<std::vector<std::vector<int>>> map(100, std::vector<std::vector<int>>(100, std::vector<int>(100, 0)));
        std::vector<std::string> input = file::readFileAsArrayString(path);

        for (const auto &l: input) {
            std::vector<int> t = utils::splitStringToInt(l, ",");
            map[t[0]][t[1]][t[2]] = 6;
        }

        std::vector<cube> transformations{{1, 0, 0}, {0, 1, 0}, {0, 0, 1}};

        for (int i = 0; i < 99; ++i) {
            for (int j = 0; j < 99; ++j) {
                for (int k = 0; k < 99; ++k) {
                    if (map[i][j][k] > 0) {
                        for (const auto& t : transformations) {
                            if (map[i + t.pos[0]][j + t.pos[1]][k + t.pos[2]] > 0) {
                                map[i + t.pos[0]][j + t.pos[1]][k + t.pos[2]]--;
                                map[i][j][k]--;
                            }
                        }
                    }
                }
            }
        }

        return std::accumulate(map.cbegin(), map.cend(), 0, [](auto lhs, const auto& rhs) {
            return std::accumulate(rhs.cbegin(), rhs.cend(), lhs, [](auto l, const auto& r) {
                return std::accumulate(r.begin(), r.end(), l);
            });
        });
    }

    int part_1(std::string_view path) {
        return countSides(path);
    }

    void bfs(int x, int y, int z,
             const std::vector<int>& min,
             const std::vector<int>& max,
             const std::vector<std::vector<std::vector<int>>>& map,
             std::vector<std::vector<std::vector<bool>>>& visited) {
        std::vector<cube> cubes;
        cubes.push_back({x, y, z});
        while (!cubes.empty()) {
            std::vector<cube> newCubes;
            for (const auto& c: cubes) {
                if (c.pos[0] < min[0] || c.pos[0] > max[0] || c.pos[1] < min[1] || c.pos[1] > max[1] || c.pos[2] < min[2] || c.pos[2] > max[2]) continue;
                if (visited[c.pos[0]][c.pos[1]][c.pos[2]]) continue;
                visited[c.pos[0]][c.pos[1]][c.pos[2]] = true;
                std::vector<cube> transformations{{-1, 0, 0}, {1, 0, 0},
                                    {0, -1, 0}, {0, 1, 0},
                                    {0, 0, -1}, {0, 0, 1}};
                for (const auto& t : transformations) {
                    for (int i = 0; i < 3; ++i) {
                        if (c.pos[i] - t.pos[i] >= min[i] && c.pos[i] - t.pos[i] <= max[i]) {
                            if (map[c.pos[0] - t.pos[0]][c.pos[1] - t.pos[1]][c.pos[2] - t.pos[2]] == 0) {
                                newCubes.push_back({c.pos[0] - t.pos[0], c.pos[1] - t.pos[1], c.pos[2] - t.pos[2]});
                            }
                            else {
                                visited[c.pos[0] - t.pos[0]][c.pos[1] - t.pos[1]][c.pos[2] - t.pos[2]] = true;
                            }
                        }
                    }
                }
            }
            cubes = newCubes;
        }
    }

    int part_2(std::string_view path) {
        int sides = countSides(path);
        std::vector<std::vector<std::vector<int>>> map(100, std::vector<std::vector<int>>(100, std::vector<int>(100, 0)));
        std::vector<std::vector<std::vector<bool>>> visited(100, std::vector<std::vector<bool>>(100, std::vector<bool>(100, 0)));

        int minX = std::numeric_limits<int>::max();
        int minY = std::numeric_limits<int>::max();
        int minZ = std::numeric_limits<int>::max();
        int maxX = 0;
        int maxY = 0;
        int maxZ = 0;

        std::vector<std::string> input = file::readFileAsArrayString(path);
        for (const auto &l: input) {
            std::vector<int> t = utils::splitStringToInt(l, ",");
            for (int i = 0; i < 3; ++i) {
                t[i] += 10;
            }
            map[t[0]][t[1]][t[2]] = 6;
            minX = std::min(minX, t[0]);
            maxX = std::max(maxX, t[0]);

            minY = std::min(minY, t[1]);
            maxY = std::max(maxY, t[1]);

            minZ = std::min(minZ, t[2]);
            maxZ = std::max(maxZ, t[2]);
        }

        minX--;
        minY--;
        minZ--;
        bfs(minX, minY, minZ, {minX, minY, minZ}, {maxX, maxY, maxZ}, map, visited);

        std::vector<cube> transformations{{-1, 0, 0}, {1, 0, 0},
                                          {0, -1, 0}, {0, 1, 0},
                                          {0, 0, -1}, {0, 0, 1}};

        for (int i = minX + 1; i < maxX; ++i) {
            for (int j = minY + 1; j < maxY; ++j) {
                for (int k = minZ + 1; k < maxZ; ++k) {
                    if (!visited[i][j][k] && map[i][j][k] == 0) {
                        for (const auto& t : transformations) {
                            sides -= (map[i - t.pos[0]][j - t.pos[1]][k - t.pos[2]] > 0);
                        }
                    }
                }
            }
        }

        return sides;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day18::part_1("../2022/day18/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day18::part_2("../2022/day18/input.in") << std::endl;

    return 0;
}
#endif
