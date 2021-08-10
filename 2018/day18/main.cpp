#include "file.h"
#include "direction.h"
#include <iostream>
#include <map>
#include <vector>

namespace aoc2018_day18 {
    enum class Type {
        Ground = 0,
        Trees = 1,
        Lumberyard = 2,
        };

    int addLineToInput(std::vector<std::vector<Type>>& map, std::string line) {
        std::vector<Type> tmp;
        for (int i = 0; i < line.size(); ++i) {
            if (line[i] == '.') tmp.push_back(Type::Ground);
            else if (line[i] == '|') tmp.push_back(Type::Trees);
            else if (line[i] == '#') tmp.push_back(Type::Lumberyard);
        }
        map.push_back(tmp);
    }

    bool inRange(int x, int low, int high) {
        return x >= low && x < high;
    }

    int solve(std::vector<std::vector<Type>> map, long long minutes = 10) {
        std::map<std::vector<std::vector<Type>>, long long> states;
        direction::Direction direction;
        for (long long m = 0; m < minutes; ++m) {
            std::vector<std::vector<Type>> tmp(map);
            for (int i = 0; i < map.size(); ++i) {
                for (int j = 0; j < map[0].size(); ++j) {
                    switch (map[i][j]) {
                        case Type::Ground: {
                            int trees = 0;
                            for (const auto &d : direction.fullDirections) {
                                if (inRange(i + d.x, 0, map.size()) &&
                                inRange(j + d.y, 0, map.size()) &&
                                map[i + d.x][j + d.y] == Type::Trees) {
                                    trees++;
                                }
                            }
                            if (trees >= 3) {
                                tmp[i][j] = Type::Trees;
                            } else {
                                tmp[i][j] = Type::Ground;
                            }
                            break;
                        }
                        case Type::Trees: {
                            int lumberyard = 0;
                            for (const auto &d : direction.fullDirections) {
                                if (inRange(i + d.x, 0, map.size()) &&
                                inRange(j + d.y, 0, map.size()) &&
                                map[i + d.x][j + d.y] == Type::Lumberyard) {
                                    lumberyard++;
                                }
                            }
                            if (lumberyard >= 3) {
                                tmp[i][j] = Type::Lumberyard;
                            } else {
                                tmp[i][j] = Type::Trees;
                            }
                            break;
                        }
                        case Type::Lumberyard: {
                            int lumberyard = 0;
                            int trees = 0;
                            for (const auto &d : direction.fullDirections) {
                                if (inRange(i + d.x, 0, map.size()) &&
                                inRange(j + d.y, 0, map.size()) &&
                                map[i + d.x][j + d.y] == Type::Lumberyard) {
                                    lumberyard++;
                                }
                                if (inRange(i + d.x, 0, map.size()) &&
                                inRange(j + d.y, 0, map.size()) &&
                                map[i + d.x][j + d.y] == Type::Trees) {
                                    trees++;
                                }
                            }
                            if (lumberyard >= 1 && trees >= 1) {
                                tmp[i][j] = Type::Lumberyard;
                            } else {
                                tmp[i][j] = Type::Ground;
                            }
                            break;
                        }
                    }
                }
            }
            if (states.find(tmp) != states.end()) {
                long long skip = m - states[tmp];
                long long skip_intervals = (minutes - m) / skip;
                m += skip * skip_intervals;
            }
            else {
                states.insert({tmp, m});
            }
            map = tmp;
        }
        int trees = 0, lumberyards = 0;
        for (const auto& line : map) {
            trees += std::count(line.begin(), line.end(), Type::Trees);
            lumberyards += std::count(line.begin(), line.end(), Type::Lumberyard);
        }

        return trees * lumberyards;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::vector<Type>> map;
        for (const auto& line : lines) {
            addLineToInput(map, line);
        }
        return solve(map);
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::vector<Type>> map;
        for (const auto& line : lines) {
            addLineToInput(map, line);
        }
        return solve(map, 1000000000);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day18::part_1("../2018/day18/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day18::part_2("../2018/day18/input.in") << std::endl;

    return 0;
}
#endif
