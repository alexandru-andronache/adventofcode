#include "file.h"
#include "utilities.h"
#include <iostream>
#include <array>
#include <deque>

namespace aoc2022_day17 {
    enum type {
        falling = 0,
        stuck = 1,
        air = 2
    };
    void insertRock(int rockIndex, std::vector<std::array<type, 7>>& map, int& min, int& max) {
        // how many empty rows do i need?
        int emptyRowsNeeded = 0;
        switch (rockIndex % 5) {
            case 0:
                emptyRowsNeeded = 4;
                break;
            case 1:
            case 2:
                emptyRowsNeeded = 6;
                break;
            case 3:
                emptyRowsNeeded = 7;
                break;
            case 4:
                emptyRowsNeeded = 5;
                break;

        }
        int emptyRows = map.size() - (max + 1);
        for (int i = emptyRows; i < emptyRowsNeeded; ++i) {
            map.push_back({type::air, type::air, type::air, type::air, type::air, type::air, type::air});
        }
        max += emptyRowsNeeded;
        if (rockIndex % 5 == 0) {
            map[max][2] = type::falling;
            map[max][3] = type::falling;
            map[max][4] = type::falling;
            map[max][5] = type::falling;
            min = max - 1;
        }
        else if (rockIndex % 5 == 1) {
            map[max][3] = map[max - 1][2] = map[max - 1][3] = map[max - 1][4] = map[max - 2][3] = type::falling;
            min = max - 3;
        }
        else if (rockIndex % 5 == 2) {
            map[max][4] = map[max - 1][4] = map[max - 2][4] = map[max - 2][3] = map[max - 2][2] = type::falling;
            min = max - 3;
        }
        else if (rockIndex % 5 == 3) {
            map[max][2] = map[max - 1][2] = map[max - 2][2] = map[max - 3][2] = type::falling;
            min = max - 4;
        }
        else if (rockIndex % 5 == 4) {
            map[max][2] = map[max][3] = map[max - 1][2] = map[max - 1][3] = type::falling;
            min = max - 2;
        }
    }

    void print(const std::vector<std::array<type, 7>>& map) {
//        for (int i = map.size() - 1; i >= 0; --i) {
//            for (int j = 0; j < 7; ++j) {
//                if (map[i][j] == type::air) {
//                    std::cout << ".";
//                }
//                else if (map[i][j] == type::stuck) {
//                    std::cout << "#";
//                }
//                else if (map[i][j] == type::falling) {
//                    std::cout << "@";
//                }
//            }
//            std::cout << "\n";
//        }
//        std::cout << "\n";
    }

    int part_1(std::string_view path) {
        std::string l = file::readFileAsString(path);
        std::vector<std::array<type, 7>> map;
        std::deque<std::array<type, 7>> map2;
        int removed_levels = 0;
        int min = 0, max = -1;
        int k = 0;
        int bad_position = -1;
        int s = l.size();

        for (int rock = 0; rock < 2022; ++rock) {
            for (int i = max; i < map.size(); ++i) {
                for (int j = 0; j < 7; ++j) {
                    if (map[i][j] == type::stuck) {
                        max = i;
                    }
                }
            }
            insertRock(rock, map, min, max);
            if (rock == bad_position) {
                print(map);
            }
            bool falling = true;

            while (falling) {
                int dir = (l[k] == '<') ? -1 : 1;
                k = (k + 1) % s;
                bool canMove = true;
                for (int i = min; i <= max; ++i) {
                    for (int j = 0; j < 7; ++j) {
                        if (map[i][j] == type::falling) {
                            if (j + dir < 0 || j + dir >= 7) {
                                canMove = false;
                            }
                            else if (map[i][j + dir] == type::stuck) {
                                canMove = false;
                            }
                        }
                    }
                }
                if (canMove) {
                    for (int i = min; i <= max; ++i) {
                        if (dir == -1) {
                            for (int j = 0; j < 7; ++j) {
                                if (map[i][j] == type::falling) {
                                    map[i][j + dir] = map[i][j];
                                    map[i][j] = type::air;
                                }
                            }
                        }
                        else {
                            for (int j = 6; j >= 0; --j) {
                                if (map[i][j] == type::falling) {
                                    map[i][j + dir] = map[i][j];
                                    map[i][j] = type::air;
                                }
                            }
                        }
                    }
                    if (rock == bad_position) {
                        print(map);
                    }
                }
                bool canFall = true;
                for (int i = min; i <= max; ++i) {
                    for (int j = 0; j < 7; ++j) {
                        if (map[i][j] == type::falling) {
                            if (i - 1 < 0) {
                                canFall = false;
                            }
                            else if (map[i - 1][j] == type::stuck) {
                                canFall = false;
                            }
                        }
                    }
                }
                if (canFall) {
                    for (int i = min; i <= max; ++i) {
                        for (int j = 0; j < 7; ++j) {
                            if (map[i][j] == type::falling) {
                                map[i - 1][j] = map[i][j];
                                map[i][j] = type::air;
                            }
                        }
                    }
                    min = std::max(0, min - 1);
                    max = std::max(0, max - 1);
                    if (rock == bad_position) {
                        print(map);
                    }
                }
                else {
                    falling = false;
                }
            }
            for (int i = min; i <= max; ++i) {
                for (int j = 0; j < 7; ++j) {
                    if (map[i][j] == type::falling) {
                        map[i][j] = type::stuck;
                    }
                }
            }

            print(map);
        }

        int sol = 0;
        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < 7; ++j) {
                if (map[i][j] == type::stuck) {
                    sol = i;
                }
            }
        }

        return sol + 1;
    }

    int part_2(std::string_view path) {
        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day17::part_1("../2022/day17/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day17::part_2("../2022/day17/input.in") << std::endl;

    return 0;
}
#endif
