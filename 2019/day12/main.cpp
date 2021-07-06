#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>
#include <array>
#include <numeric>

namespace aoc2019_day12 {
    struct moon {
        std::array<int, 3> position;
        std::array<int, 3> velocity;
    };

    unsigned long long solveOneDimension(const std::vector<int>& positions) {
        int steps = 0;
        std::vector<std::pair<int, int>> moons(positions.size());
        for (int i = 0; i < positions.size(); ++i) {
            moons[i].first = positions[i];
            moons[i].second = 0;
        }
        std::set<std::vector<std::pair<int, int>>> states;
        while (states.find(moons) == states.end()) {
            states.insert(moons);
            std::vector<std::pair<int, int>> newMoons = moons;
            for (int i = 0; i < newMoons.size(); ++i) {
                for (int j = i + 1; j < newMoons.size(); ++j) {
                    if (moons[i].first < moons[j].first) {
                        newMoons[i].second++;
                        newMoons[j].second--;
                    }
                    else if (moons[i].first > moons[j].first) {
                        newMoons[i].second--;
                        newMoons[j].second++;
                    }
                }
            }
            for (auto & newMoon : newMoons) {
                newMoon.first += newMoon.second;
            }
            moons = newMoons;
            steps++;
        }
        return steps;
    }

    long long part_1(const std::vector<std::vector<int>>& positions, int steps = 1000) {
        std::vector<moon> moons(positions.size());
        for (int i = 0; i < moons.size(); ++i) {
            moons[i].position = {positions[i][0], positions[i][1], positions[i][2]};
        }

        for (int k = 0; k < steps; ++k) {
            std::vector<moon> newMoons = moons;
            for (int i = 0; i < moons.size(); ++i) {
                for (int j = i + 1; j < moons.size(); ++j) {
                    for (int l = 0; l < moons[i].position.size(); ++l) {
                        if (moons[i].position[l] < moons[j].position[l]) {
                            newMoons[i].velocity[l]++;
                            newMoons[j].velocity[l]--;
                        }
                        else if (moons[i].position[l] > moons[j].position[l]) {
                            newMoons[i].velocity[l]--;
                            newMoons[j].velocity[l]++;
                        }
                    }
                }
            }

            for (auto & newMoon : newMoons) {
                for (int j = 0; j < newMoon.position.size(); ++j) {
                    newMoon.position[j] += newMoon.velocity[j];
                }
            }

            moons = newMoons;
        }

        long long sum = 0;
        for (const auto & moon : moons) {
            sum += (std::abs(moon.position[0]) + std::abs(moon.position[1]) + std::abs(moon.position[2])) *
                    (std::abs(moon.velocity[0]) + std::abs(moon.velocity[1]) + std::abs(moon.velocity[2]));
        }

        return sum;
    }

    unsigned long long part_2(const std::vector<std::vector<int>>& positions) {
        unsigned long long steps1 = solveOneDimension({positions[0][0], positions[1][0], positions[2][0], positions[3][0]});
        unsigned long long steps2 = solveOneDimension({positions[0][1], positions[1][1], positions[2][1], positions[3][1]});
        unsigned long long steps3 = solveOneDimension({positions[0][2], positions[1][2], positions[2][2], positions[3][2]});
        return std::lcm(std::lcm(steps1, steps2), steps3);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day12::part_1({{5, -1, 5}, {0, -14, 2}, {16, 4, 0}, {18, 1, 16}}) << std::endl;
    std::cout << "Part 2: " << aoc2019_day12::part_2({{5, -1, 5}, {0, -14, 2}, {16, 4, 0}, {18, 1, 16}}) << std::endl;

    return 0;
}
#endif
