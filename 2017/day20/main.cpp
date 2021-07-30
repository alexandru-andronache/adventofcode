#include "file.h"
#include "utilities.h"
#include "math_util.h"
#include <iostream>
#include <set>

namespace aoc2017_day20 {
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::vector<int>> particles;
        for (const auto& line : lines) {
            particles.emplace_back(utils::splitStringToInt(line, " p=<>,va"));
        }

        auto it = std::min_element(particles.begin(), particles.end(), [](auto p1, auto p2) {
            int sumAcc1 = std::abs(p1[8]) + std::abs(p1[7]) + std::abs(p1[6]);
            int sumAcc2 = std::abs(p2[8]) + std::abs(p2[7]) + std::abs(p2[6]);
            if (sumAcc1 != sumAcc2) {
                return sumAcc1 < sumAcc2;
            }
            int sumVel1 = std::abs(p1[5]) + std::abs(p1[4]) + std::abs(p1[3]);
            int sumVel2 = std::abs(p2[5]) + std::abs(p2[4]) + std::abs(p2[3]);
            if (sumVel1 != sumVel2) {
                return sumVel1 < sumVel2;
            }
            int sumPos1 = std::abs(p1[2]) + std::abs(p1[1]) + std::abs(p1[0]);
            int sumPos2 = std::abs(p2[2]) + std::abs(p2[1]) + std::abs(p2[0]);
            return sumPos1 < sumPos2;
        });

        return std::distance(particles.begin(), it);
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::vector<int>> particles;
        for (const auto& line : lines) {
            particles.emplace_back(utils::splitStringToInt(line, " p=<>,va"));
        }

        std::vector<std::set<int>> collisions(10000, std::set<int>());
        std::vector<bool> collided(particles.size(), false);

        for (int i = 0; i < particles.size(); ++i) {
            for (int j = i + 1; j < particles.size(); ++j) {
                auto x = math::solvequadratic((double)(particles[i][8] - particles[j][8]) / 2, particles[i][5] - particles[j][5] + (double)(particles[i][8] - particles[j][8]) / 2, particles[i][2] - particles[j][2]);
                auto y = math::solvequadratic((double)(particles[i][7] - particles[j][7]) / 2, particles[i][4] - particles[j][4] + (double)(particles[i][7] - particles[j][7]) / 2, particles[i][1] - particles[j][1]);
                auto z = math::solvequadratic((double)(particles[i][6] - particles[j][6]) / 2, particles[i][3] - particles[j][3] + (double)(particles[i][6] - particles[j][6]) / 2, particles[i][0] - particles[j][0]);

                int sol1 = -1;
                int sol2 = -1;
                if (x.first != 0 || x.second != 0) {
                    if (x.first > 0) {
                        if ((x.first == y.first || x.first == y.second) &&
                        (x.first == z.first || x.first == z.second)) {
                            sol1 = x.first;
                        }
                    }
                    if (x.second > 0) {
                        if ((x.second == y.first || x.second == y.second) &&
                        (x.second == z.first || x.second == z.second)) {
                            sol1 = x.second;
                        }
                    }
                }
                else if (y.first != 0 || y.second != 0) {
                    if (y.first > 0) {
                        if (z.first == y.first || z.second == y.first) {
                            sol1 = y.first;
                        }
                    }
                    if (y.second > 0) {
                        if (z.first == y.second || z.second == y.second) {
                            sol2 = y.second;
                        }
                    }
                }
                else if (z.first != 0 || z.second != 0) {
                    sol1 = z.first;
                    sol2 = z.second;
                }
                int sol = -1;
                if (sol1 > 0 && sol2 > 0) {
                    sol = std::min(sol1, sol2);
                }
                else if (sol1 > 0) {
                    sol = sol1;
                }
                else if (sol2 > 0) {
                    sol = sol2;
                }
                if (sol != -1) {
                    collisions[sol].insert(i);
                    collisions[sol].insert(j);
                }
            }
        }

        for (const auto& s : collisions) {
            int nr = 0;
            for (const auto& p : s) {
                if (!collided[p]) {
                    nr++;
                }
            }
            if (nr > 1) {
                for (const auto& p : s) {
                    collided[p] = true;
                }
            }
        }

        int sol = 0;
        for (const auto& c: collided) {
            if (!c) sol++;
        }

        return sol;
    }

}


#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day20::part_1("../2017/day20/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day20::part_2("../2017/day20/input.in") << std::endl;

    return 0;
}
#endif
