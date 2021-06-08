#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>

namespace aoc2020_day17 {
    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int steps = 6;
        std::vector<std::vector<std::vector<bool>>> map(input.size() + 2 * steps,
                                                        std::vector<std::vector<bool>>(input[0].size() + 2 * steps,
                                                                                       std::vector<bool>(1 + 2 * steps,
                                                                                                         false)));

        int centruX = steps;
        int centruY = steps;
        int centruZ = steps;

        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                if (input[i][j] == '#') {
                    map[i + centruX][j + centruY][0 + centruZ] = true;
                }
            }
        }

        for (int step = 0; step < 6; ++step) {
            std::vector<std::vector<std::vector<bool>>> map2 = map;

            for (int i = 0; i < map2.size(); ++i) {
                for (int j = 0; j < map2[0].size(); ++j) {
                    for (int k = 0; k < map2[0][0].size(); ++k) {
                        int sum = 0;
                        for (int ii = -1; ii <= 1; ++ii) {
                            for (int jj = -1; jj <= 1; ++jj) {
                                for (int kk = -1; kk <= 1; ++kk) {
                                    if (ii == 0 && jj == 0 && kk == 0) {

                                    } else {
                                        if (i + ii >= 0 && i + ii < map.size() &&
                                            j + jj >= 0 && j + jj < map[0].size() &&
                                            k + kk >= 0 && k + kk < map[0][0].size()) {
                                            if (map[i + ii][j + jj][k + kk]) {
                                                sum++;
                                            }
                                        }
                                    }
                                }
                            }
                        }

                        if (i >= 0 && i < map.size() &&
                            j >= 0 && j < map[0].size() &&
                            k >= 0 && k < map[0][0].size() && map[i][j][k]) {
                            if (sum == 2 || sum == 3) {
                                map2[i][j][k] = true;
                            } else {
                                map2[i][j][k] = false;
                            }
                        } else {
                            if (sum == 3) {
                                map2[i][j][k] = true;
                            } else {
                                map2[i][j][k] = false;
                            }
                        }
                    }
                }
            }

            map = map2;
        }

        int sum = 0;
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                for (int k = 0; k < map[0][0].size(); ++k) {
                    if (map[i][j][k]) {
                        sum++;
                    }
                }
            }
        }

        return sum;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int steps = 6;
        std::vector<std::vector<std::vector<std::vector<bool>>>> map(input.size() + 2 * steps,
                                                                     std::vector<std::vector<std::vector<bool>>>(
                                                                             input[0].size() + 2 * steps,
                                                                             std::vector<std::vector<bool>>(
                                                                                     1 + 2 * steps,
                                                                                     std::vector<bool>(1 + 2 * steps,
                                                                                                       false))));

        int centruX = steps;
        int centruY = steps;
        int centruZ = steps;
        int centruW = steps;

        for (int i = 0; i < input.size(); ++i) {
            for (int j = 0; j < input[0].size(); ++j) {
                if (input[i][j] == '#') {
                    map[i + centruX][j + centruY][0 + centruZ][0 + centruW] = true;
                }
            }
        }

        for (int step = 0; step < 6; ++step) {
            std::vector<std::vector<std::vector<std::vector<bool>>>> map2 = map;

            for (int i = 0; i < map2.size(); ++i) {
                for (int j = 0; j < map2[0].size(); ++j) {
                    for (int k = 0; k < map2[0][0].size(); ++k) {
                        for (int l = 0; l < map2[0][0][0].size(); ++l) {
                            int sum = 0;
                            for (int ii = -1; ii <= 1; ++ii) {
                                for (int jj = -1; jj <= 1; ++jj) {
                                    for (int kk = -1; kk <= 1; ++kk) {
                                        for (int ll = -1; ll <= 1; ++ll) {
                                            if (ii == 0 && jj == 0 && kk == 0 && ll == 0) {

                                            } else {
                                                if (i + ii >= 0 && i + ii < map.size() &&
                                                    j + jj >= 0 && j + jj < map[0].size() &&
                                                    k + kk >= 0 && k + kk < map[0][0].size() &&
                                                    l + ll >= 0 && l + ll < map[0][0][0].size()) {
                                                    if (map[i + ii][j + jj][k + kk][l + ll]) {
                                                        sum++;
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }


                            if (i >= 0 && i < map.size() &&
                                j >= 0 && j < map[0].size() &&
                                k >= 0 && k < map[0][0].size() &&
                                l >= 0 && l < map[0][0][0].size() &&
                                map[i][j][k][l]) {
                                if (sum == 2 || sum == 3) {
                                    map2[i][j][k][l] = true;
                                } else {
                                    map2[i][j][k][l] = false;
                                }
                            } else {
                                if (sum == 3) {
                                    map2[i][j][k][l] = true;
                                } else {
                                    map2[i][j][k][l] = false;
                                }
                            }
                        }
                    }
                }
            }

            map = map2;
        }

        int sum = 0;
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[0].size(); ++j) {
                for (int k = 0; k < map[0][0].size(); ++k) {
                    for (int l = 0; l < map[0][0][0].size(); ++l) {
                        if (map[i][j][k][l]) {
                            sum++;
                        }
                    }
                }
            }
        }

        return sum;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day17::part_1("../2020/day17/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day17::part_2("../2020/day17/input.in") << std::endl;

    return 0;
}
#endif
