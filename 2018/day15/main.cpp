#include "file.h"
#include <iostream>
#include <optional>
#include <vector>

namespace aoc2018_day15 {
    enum class Type {
        Elf = 0,
        Goblin = 1,
        Wall = 3,
        Nothing = 5,
        Visited = 6
    };

    int operator-(Type a, Type b) {
        return (int)a - (int)b;
    }

    struct Point {
        Type type;
        int life = 200;
        int attack = 3;
        bool updated = false;
        int x;
        int y;
    };

    void addRowToMap(std::string str, std::vector<std::vector<Point>>& map) {
        std::vector<Point> line;
        for (const auto& c : str) {
            if (c == '#') {
                line.push_back({Type::Wall});
            }
            else if (c == '.') {
                line.push_back({Type::Nothing});
            }
            else if (c == 'G') {
                line.push_back({Type::Goblin});
            }
            else if (c == 'E') {
                line.push_back({Type::Elf});
            }
        }
        map.push_back(line);
    }

    std::optional<std::pair<int, int>> canAttack(const std::vector<std::vector<Point>>& map, u_int x, u_int y) {
        int min = std::numeric_limits<int>::max();
        for (int i = -1; i <= 1; i++) {
            for (int j = std::abs(i) - 1; j <= 1; j += 2) {
                if (x + i >= 0 && x + i <= map.size() &&
                y + j >= 0 && y + j <= map.size() &&
                std::abs(map[x + i][y + j].type - map[x][y].type) == 1) {
                    min = std::min(min, map[x + i][y + j].life);
                }
            }
        }

        for (int i = -1; i <= 1; i++) {
            for (int j = std::abs(i) - 1; j <= 1; j += 2) {
                if (x + i >= 0 && x + i <= map.size() &&
                y + j >= 0 && y + j <= map.size() &&
                std::abs(map[x + i][y + j].type - map[x][y].type) == 1) {
                    if (min == map[x + i][y + j].life) {
                        return std::make_pair(x + i, y + j);
                    }
                }
            }
        }

        return std::nullopt;
    }

    //first returns if the attack was successful and the second if the attack killed someone
    std::pair<bool, bool> attack(std::vector<std::vector<Point>>& map, u_int x, u_int y) {
        auto attack = canAttack(map, x, y);
        if (attack.has_value()) {
            map[attack->first][attack->second].life -= map[x][y].attack;
            if (map[attack->first][attack->second].life <= 0) {
                map[attack->first][attack->second].type = Type::Nothing;
                return std::make_pair(true, true);
            }
            return std::make_pair(true, false);
        }
        return std::make_pair(false, false);
    }

    std::optional<std::pair<int, int>> canMove(std::vector<std::vector<Point>> map, u_int x, u_int y) {
        Type monster = map[x][y].type;
        std::vector<std::pair<int, int>> path;
        path.push_back({x, y});
        int begin = 0, end = 0;
        while (begin <= end) {
            for (int i = begin; i <= end; ++i) {
                x = path[i].first;
                y = path[i].second;

                for (int i = -1; i <= 1; i++) {
                    for (int j = std::abs(i) - 1; j <= 1; j += 2) {
                        if (x + i >= 0 && x + i <= map.size() &&
                        y + j >= 0 && y + j <= map.size()) {
                            if (map[x + i][y + j].type == Type::Nothing) {
                                if (map[x][y].type == Type::Goblin || map[x][y].type == Type::Elf) {
                                    map[x + i][y + j].x = i;
                                    map[x + i][y + j].y = j;
                                }
                                else {
                                    map[x + i][y + j].x = map[x][y].x;
                                    map[x + i][y + j].y = map[x][y].y;
                                }
                                map[x + i][y + j].type = Type::Visited;
                                path.push_back({x + i, y + j});
                            }
                            else if (std::abs(monster - map[x + i][y + j].type) == 1) {
                                return std::make_pair(map[x][y].x, map[x][y].y);
                            }
                        }
                    }
                }
            }
            begin = end + 1;
            end = path.size() - 1;
        }
        return std::nullopt;
    }

    // returns score + number of dead elfs
    std::pair<int, int> fight(std::vector<std::vector<Point>> map) {
        int rounds = 0;
        int initialNrElfs = 0;
        for (int i = 0; i < map.size(); ++i) {
            initialNrElfs += std::count_if(map[i].begin(), map[i].end(), [](const auto& m) {
                return m.type == Type::Elf;
            });
        }
        while (true) {
            rounds++;
            bool lastAttackKilled = false;
            for (int i = 0; i < map.size(); ++i) {
                for (int j = 0; j < map[0].size(); ++j) {
                    if ((map[i][j].type == Type::Goblin || map[i][j].type == Type::Elf) &&
                    (!map[i][j].updated)) {
                        auto a = attack(map, i, j);
                        lastAttackKilled = a.second;
                        if (!a.first) {
                            auto move = canMove(map, i, j);
                            if (move.has_value()) {
                                int x = move->first;
                                int y = move->second;
                                map[i + x][j + y] = map[i][j];
                                auto a = attack(map, i + x, j + y);
                                lastAttackKilled = a.second;
                                map[i + x][j + y].updated = true;
                                map[i][j].type = Type::Nothing;
                            }
                        }
                    }
                }
            }

            for (int i = 0; i < map.size(); ++i) {
                for (int j = 0; j < map[0].size(); ++j) {
                    map[i][j].updated = false;
                }
            }

            int nrElf = 0, nrGoblin = 0;
            for (int i = 0; i < map.size(); ++i) {
                nrElf += std::count_if(map[i].begin(), map[i].end(), [](const auto& m) {
                    return m.type == Type::Elf;
                });
                nrGoblin += std::count_if(map[i].begin(), map[i].end(), [](const auto& m) {
                    return m.type == Type::Goblin;
                });
            }
            if (nrElf == 0 || nrGoblin == 0) {
                int sum = 0;
                for (int i = 0; i < map.size(); ++i) {
                    for (int j = 0; j < map[0].size(); ++j) {
                        if (map[i][j].type == Type::Goblin || map[i][j].type == Type::Elf) {
                            sum += map[i][j].life;
                        }
                    }
                }
                if (lastAttackKilled)
                    return std::make_pair(sum * rounds, initialNrElfs - nrElf);
                return std::make_pair(sum * (rounds - 1), initialNrElfs - nrElf);
            }
        }
    }

    int part_1(std::string_view path) {
        std::vector<std::vector<Point>> map;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            addRowToMap(line, map);
        }
        return fight(map).first;
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<Point>> map;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            addRowToMap(line, map);
        }

        int li = 4, ls = 200;
        int sol = 0;
        while (li <= ls) {
            int m = (li + ls) / 2;
            std::vector<std::vector<Point>> tmpMap(map);
            for (auto& line : tmpMap) {
                for (auto& point : line) {
                    if (point.type == Type::Elf) {
                        point.attack = m;
                    }
                }
            }

            auto result = fight(tmpMap);
            if (result.second == 0) {
                ls = m - 1;
                sol = result.first;
            }
            else {
                li = m + 1;
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day15::part_1("../2018/day15/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2018_day15::part_2("../2018/day15/input.in") << std::endl;

    return 0;
}
#endif
