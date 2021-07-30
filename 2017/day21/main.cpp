#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2017_day21 {
    bool compare(std::string_view grid, std::string_view rule) {
        std::string r(rule);
        if (r.size() != grid.size()) {
            return false;
        }
        int size = r.size() == 5 ? 2 : 3;
        //    rotate
        for (int i = 0; i < 5; ++i) {
            if (grid == r) {
                return true;
            }
            {
                std::string flip(r);
                for (int i = 0; i < size; ++i) {
                    std::swap(flip[i], flip[flip.size() - size + i]);
                }
                if (flip == grid) {
                    return true;
                }
            }

            {
                std::string flip(r);
                for (int i = 0; i < size; ++i) {
                    std::swap(flip[i + size], flip[i + size + size - 1]);
                }
                if (flip == grid) {
                    return true;
                }
            }

            std::string rule90(r);
            if (size == 2) {
                rule90[0] = r[3];
                rule90[1] = r[0];
                rule90[3] = r[4];
                rule90[4] = r[1];
            } else {
                rule90[0] = r[8];
                rule90[1] = r[4];
                rule90[2] = r[0];

                rule90[4] = r[9];
                rule90[5] = r[5];
                rule90[6] = r[1];

                rule90[8] = r[10];
                rule90[9] = r[6];
                rule90[10] = r[2];
            }
            r = rule90;
        }

        return false;
    }

    int solve(const std::vector<std::pair<std::string, std::string>>& rules, int rounds) {
        std::vector<std::vector<char>> grid;
        grid.push_back({'.', '#', '.'});
        grid.push_back({'.', '.', '#'});
        grid.push_back({'#', '#', '#'});

        for (int round = 0; round < rounds; ++round) {
            std::vector<std::vector<char>> newGrid;
            int size = 3;
            int extra = 4;
            if (grid.size() % 2 == 0) {
                size = 2;
                extra = 3;
            }
            for (int i = 0; i < grid.size(); i += size) {
                std::vector<std::vector<char>> line(extra, std::vector<char>());
                for (int j = 0; j < grid.size(); j += size) {
                    std::string s;
                    for (int a = i; a < i + size; ++a) {
                        for (int b = j; b < j + size; ++b) {
                            s += grid[a][b];
                        }
                        if (a != i + size - 1)
                            s += '/';
                    }
                    for (const auto &r : rules) {
                        if (compare(s, r.first)) {
                            int ll = 0;
                            for (int ii = 0; ii < extra; ++ii) {
                                for (int jj = 0; jj < extra; ++jj) {
                                    line[ii].push_back(r.second[ll]);
                                    ll++;
                                }
                                ll++;
                            }
                        }
                    }
                }
                newGrid.insert(newGrid.end(), line.begin(), line.end());
            }

            grid = newGrid;
        }

        int sol = 0;
        for (const auto& line : grid) {
            for (const auto& c : line) {
                if (c == '#') sol++;
            }
        }

        return sol;
    }

    int part_1(std::string_view path) {
        std::vector<std::pair<std::string, std::string>> rules;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " =>");
            rules.emplace_back(tokens[0], tokens[1]);
        }
        return solve(rules, 5);
    }

    int part_2(std::string_view path) {
        std::vector<std::pair<std::string, std::string>> rules;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " =>");
            rules.emplace_back(tokens[0], tokens[1]);
        }
        return solve(rules, 18);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day21::part_1("../2017/day21/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day21::part_2("../2017/day21/input.in") << std::endl;

    return 0;
}
#endif
