#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <vector>
#include <queue>

namespace aoc2018_day23 {
    long long manhattanDistance(const std::array<long long, 3>& point1, const std::array<long long, 3>& point2) {
        long long d = 0;
        for (int i = 0; i < point1.size(); ++i) {
            d += abs(point1[i] - point2[i]);
        }
        return d;
    }

    int nrIntersects(const std::vector<std::pair<std::array<long long, 3>, long long>>& input,
                     const std::tuple<long long, long long, long long, long long, long long, long long>& cube) {
        int nr = 0;
        auto [x1, x2, y1, y2, z1, z2] = cube;
        for (const auto& i : input) {
            int dist = 0;
            if (i.first[0] < x1) {
                dist += abs(x1 - i.first[0]);
            }
            else if (i.first[0] > x2) {
                dist += abs(x2 - i.first[0]);
            }

            if (i.first[1] < y1) {
                dist += abs(y1 - i.first[1]);
            }
            else if (i.first[1] > y2) {
                dist += abs(y2 - i.first[1]);
            }

            if (i.first[2] < z1) {
                dist += abs(z1 - i.first[2]);
            }
            else if (i.first[2] > z2) {
                dist += abs(z2 - i.first[2]);
            }

            if (dist <= i.second) {
                nr++;
            }
        }
        return nr;
    }

    int part_1(std::string_view path) {
        std::vector<std::pair<std::array<long long, 3>, long long>> input;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "=<>, ");
            input.push_back({{std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3])}, std::stoi(tokens[5])});
        }

        auto nanobot = *std::max_element(input.begin(), input.end(), [](auto a, auto b) {
            return a.second < b.second;
        });

        int sol = 0;
        for (const auto& x : input) {
            if (manhattanDistance(x.first, nanobot.first) <= nanobot.second) {
                sol++;
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::pair<std::array<long long, 3>, long long>> input;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "=<>, ");
            input.push_back({{std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3])}, std::stoi(tokens[5])});
        }

        long long minX = std::numeric_limits<long long>::max();
        long long minY = std::numeric_limits<long long>::max();
        long long minZ = std::numeric_limits<long long>::max();

        long long maxX = std::numeric_limits<long long>::min();
        long long maxY = std::numeric_limits<long long>::min();
        long long maxZ = std::numeric_limits<long long>::min();

        for (const auto& i : input) {
            minX = std::min(minX, i.first[0]);
            minY = std::min(minY, i.first[1]);
            minZ = std::min(minZ, i.first[2]);

            maxX = std::max(maxX, i.first[0]);
            maxY = std::max(maxY, i.first[1]);
            maxZ = std::max(maxZ, i.first[2]);
        }

        auto cmp = [](std::tuple<long long, long long, long long, long long, long long, long long, int> left,
                std::tuple<long long, long long, long long, long long, long long, long long, int> right) {
            auto [a1, a2, a3, a4, a5, a6, l] = left;
            auto [b1, b2, b3, b4, b5, b6, r] = right;
            return l < r;
        };

        std::priority_queue<std::tuple<long long, long long, long long, long long, long long, long long, int>,
        std::vector<std::tuple<long long, long long, long long, long long, long long, long long, int>>,
        decltype(cmp)> cubes(cmp);


        cubes.push({minX, maxX, minY, maxY, minZ, maxZ, input.size()});
        int maxIntersections = std::numeric_limits<int>::min();
        std::array<long long, 3> finalPoint;

        int prevIntersect = 0;
        while (!cubes.empty()) {
            auto [x1, x2, y1, y2, z1, z2, intersect] = cubes.top();
            cubes.pop();

            if (x1 == x2 && y1 == y2 && z1 == z2) {
                int intersections = 0;
                for (const auto& i : input) {
                    if (manhattanDistance(i.first, {x1, y1, z1}) <= i.second) {
                        intersections++;
                    }
                }
                if (maxIntersections == intersections &&
                manhattanDistance({0, 0, 0}, {x1, y1, z1}) < manhattanDistance({0, 0, 0}, finalPoint)) {
                    finalPoint = {x1, y1, z1};
                }
                if (maxIntersections < intersections) {
                    maxIntersections = intersections;
                    finalPoint = {x1, y1, z1};
                }
            }
            else if (intersect >= maxIntersections) {
                int interesct1 = nrIntersects(input, {x1, x1 + (x2 - x1) / 2, y1, y1 + (y2 - y1) / 2, z1, z1 + (z2 - z1) / 2});
                if (interesct1 >= maxIntersections) {
                    cubes.push({x1, x1 + (x2 - x1) / 2, y1, y1 + (y2 - y1) / 2, z1, z1 + (z2 - z1) / 2, interesct1});
                }
                int intersect2 = nrIntersects(input, {x1, x1 + (x2 - x1) / 2, y1, y1 + (y2 - y1) / 2, std::min(z1 + (z2 - z1) / 2 + 1, z2), z2});
                if (intersect2 >= maxIntersections) {
                    cubes.push({x1, x1 + (x2 - x1) / 2, y1, y1 + (y2 - y1) / 2, std::min(z1 + (z2 - z1) / 2 + 1, z2), z2, intersect2});
                }

                int intersect3 = nrIntersects(input, {x1, x1 + (x2 - x1) / 2, std::min(y1 + (y2 - y1) / 2 + 1, y2), y2, z1, z1 + (z2 - z1) / 2});
                if (intersect3 >= maxIntersections) {
                    cubes.push({x1, x1 + (x2 - x1) / 2, std::min(y1 + (y2 - y1) / 2 + 1, y2), y2, z1, z1 + (z2 - z1) / 2, intersect3});
                }
                int intersect4 = nrIntersects(input, {x1, x1 + (x2 - x1) / 2, std::min(y1 + (y2 - y1) / 2 + 1, y2), y2, std::min(z1 + (z2 - z1) / 2 + 1, z2), z2});
                if (intersect4 >= maxIntersections) {
                    cubes.push({x1, x1 + (x2 - x1) / 2, std::min(y1 + (y2 - y1) / 2 + 1, y2), y2, std::min(z1 + (z2 - z1) / 2 + 1, z2), z2, intersect4});
                }

                int intersect5 = nrIntersects(input, {std::min(x1 + (x2 - x1) / 2 + 1, x2), x2, y1, y1 + (y2 - y1) / 2, z1, z1 + (z2 - z1) / 2});
                if (intersect5 >= maxIntersections) {
                    cubes.push({std::min(x1 + (x2 - x1) / 2 + 1, x2), x2, y1, y1 + (y2 - y1) / 2, z1, z1 + (z2 - z1) / 2, intersect5});
                }
                int intersect6 = nrIntersects(input, {std::min(x1 + (x2 - x1) / 2 + 1, x2), x2, y1, y1 + (y2 - y1) / 2, std::min(z1 + (z2 - z1) / 2 + 1, z2), z2});
                if (intersect6 >= maxIntersections) {
                    cubes.push({std::min(x1 + (x2 - x1) / 2 + 1, x2), x2, y1, y1 + (y2 - y1) / 2, std::min(z1 + (z2 - z1) / 2 + 1, z2), z2, intersect6});
                }

                int intersect7 = nrIntersects(input, {std::min(x1 + (x2 - x1) / 2 + 1, x2), x2, std::min(y1 + (y2 - y1) / 2 + 1, y2), y2, z1, z1 + (z2 - z1) / 2});
                if (intersect7 >= maxIntersections) {
                    cubes.push({std::min(x1 + (x2 - x1) / 2 + 1, x2), x2, std::min(y1 + (y2 - y1) / 2 + 1, y2), y2, z1, z1 + (z2 - z1) / 2, intersect7});
                }
                int intersect8 = nrIntersects(input, {std::min(x1 + (x2 - x1) / 2 + 1, x2), x2, std::min(y1 + (y2 - y1) / 2 + 1, y2), y2, std::min(z1 + (z2 - z1) / 2 + 1, z2), z2});
                if (intersect8 >= maxIntersections) {
                    cubes.push({std::min(x1 + (x2 - x1) / 2 + 1, x2), x2, std::min(y1 + (y2 - y1) / 2 + 1, y2), y2, std::min(z1 + (z2 - z1) / 2 + 1, z2), z2, intersect8});
                }
            }
        }

        return manhattanDistance(finalPoint, {0, 0, 0});
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day23::part_1("../2018/day23/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day23::part_2("../2018/day23/input.in") << std::endl;

    return 0;
}
#endif
