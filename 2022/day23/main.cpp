#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <complex>
#include <vector>

namespace aoc2022_day23 {
    struct tentative {
        std::complex<int> oldPos;
    };
    struct elf {
        bool exist;
        std::vector<tentative> wantToMove;
    };
    const int N = 300;
    int part_1(std::string_view path) {
        std::vector<std::vector<elf>> elfs(N, std::vector<elf>(N, {false, {}}));
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        int startX = N / 2, startY = N / 2;
        for (const auto& l : lines) {
            startY = N / 2;
            for (const auto& c : l) {
                if (c == '#') {
                    elfs[startX][startY].exist = true;
                }
                startY++;
            }
            startX++;
        }

        std::vector<std::complex<int>> generalDirections;
        generalDirections.emplace_back(-1, 0);
        generalDirections.push_back({1, 0});
        generalDirections.push_back({0, -1});
        generalDirections.push_back({0, 1});

        for (int round = 0; round < 10; ++round) {
            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    if (elfs[x][y].exist) {
                        if (elfs[x + 1][y - 1].exist || elfs[x + 1][y].exist || elfs[x + 1][y + 1].exist ||
                            elfs[x][y - 1].exist || elfs[x][y + 1].exist ||
                            elfs[x - 1][y - 1].exist || elfs[x - 1][y].exist || elfs[x - 1][y + 1].exist) {
                            for (const auto &dir: generalDirections) {
                                if (dir.real() == 0) {
                                    if (!elfs[x - 1][y + dir.imag()].exist &&
                                        !elfs[x][y + dir.imag()].exist &&
                                        !elfs[x + 1][y + dir.imag()].exist) {
                                        elfs[x][y + dir.imag()].wantToMove.push_back({{x, y}});
                                        break;
                                    }
                                } else {
                                    if (!elfs[x + dir.real()][y - 1].exist &&
                                        !elfs[x + dir.real()][y].exist &&
                                        !elfs[x + dir.real()][y + 1].exist) {
                                        elfs[x + dir.real()][y].wantToMove.push_back({{x, y}});
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    if (elfs[x][y].wantToMove.size() == 1) {
                        std::complex<int> oldPos = elfs[x][y].wantToMove[0].oldPos;
                        elfs[x][y].exist = true;
                        elfs[oldPos.real()][oldPos.imag()].exist = false;
                    }
                    elfs[x][y].wantToMove.clear();
                }
            }

            auto dirToRemove = generalDirections.front();
            std::erase(generalDirections, generalDirections.front());
            generalDirections.push_back(dirToRemove);
        }

        int minX = N, minY = N, maxX = 0, maxY = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (elfs[i][j].exist) {
                    minX = std::min(minX, i);
                    minY = std::min(minY, j);
                    maxX = std::max(maxX, i);
                    maxY = std::max(maxY, j);
                }
            }
        }

        int sol = 0;
        for (int i = minX; i <= maxX; ++i) {
            for (int j = minY; j <= maxY; ++j) {
                if (!elfs[i][j].exist) {
                    sol++;
                }
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<elf>> elfs(N, std::vector<elf>(N, {false, {}}));
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::complex<int>> positions;

        int startX = N / 2, startY = N / 2;
        for (const auto& l : lines) {
            startY = N / 2;
            for (const auto& c : l) {
                if (c == '#') {
                    elfs[startX][startY].exist = true;
                    positions.emplace_back(startX, startY);
                }
                startY++;
            }
            startX++;
        }

        std::vector<std::complex<int>> generalDirections;
        generalDirections.emplace_back(-1, 0);
        generalDirections.push_back({1, 0});
        generalDirections.push_back({0, -1});
        generalDirections.push_back({0, 1});

        int round = 1;

        while (true) {
            std::vector<std::complex<int>> newPositions;
            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    if (elfs[x][y].exist) {
                        if (elfs[x + 1][y - 1].exist || elfs[x + 1][y].exist || elfs[x + 1][y + 1].exist ||
                            elfs[x][y - 1].exist || elfs[x][y + 1].exist ||
                            elfs[x - 1][y - 1].exist || elfs[x - 1][y].exist || elfs[x - 1][y + 1].exist) {
                            for (const auto &dir: generalDirections) {
                                if (dir.real() == 0) {
                                    if (!elfs[x - 1][y + dir.imag()].exist &&
                                        !elfs[x][y + dir.imag()].exist &&
                                        !elfs[x + 1][y + dir.imag()].exist) {
                                        elfs[x][y + dir.imag()].wantToMove.push_back({{x, y}});
                                        break;
                                    }
                                } else {
                                    if (!elfs[x + dir.real()][y - 1].exist &&
                                        !elfs[x + dir.real()][y].exist &&
                                        !elfs[x + dir.real()][y + 1].exist) {
                                        elfs[x + dir.real()][y].wantToMove.push_back({{x, y}});
                                        break;
                                    }
                                }
                            }
                        }
                    }
                }
            }

            bool hasMoved = false;
            for (int x = 0; x < N; ++x) {
                for (int y = 0; y < N; ++y) {
                    if (elfs[x][y].wantToMove.size() == 1) {
                        std::complex<int> oldPos = elfs[x][y].wantToMove[0].oldPos;
                        elfs[x][y].exist = true;
                        elfs[oldPos.real()][oldPos.imag()].exist = false;
                        hasMoved = true;
                        newPositions.push_back({x, y});
                    }
                    elfs[x][y].wantToMove.clear();
                }
            }

            positions = newPositions;

            if (!hasMoved) {
                return round;
            }
            round++;

            auto dirToRemove = generalDirections.front();
            std::erase(generalDirections, generalDirections.front());
            generalDirections.push_back(dirToRemove);
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day23::part_1("../2022/day23/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day23::part_2("../2022/day23/input.in") << std::endl;

    return 0;
}
#endif
