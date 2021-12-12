#include "file.h"
#include "utilities.h"
#include "StringToIntMap.h"
#include "string_util.h"
#include <iostream>
#include <vector>

namespace aoc2021_day12 {
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        stringtointmap::StringToIntMap caves;
        int sol = 0;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "-");
            caves.addString(tokens[0]);
            caves.addString(tokens[1]);
        }

        std::vector<std::vector<bool>> map(caves.getSize(), std::vector<bool>(caves.getSize(), false));
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "-");
            map[caves.getIndex(tokens[0])][caves.getIndex(tokens[1])] = true;
            map[caves.getIndex(tokens[1])][caves.getIndex(tokens[0])] = true;
        }
        std::vector<bool> upperCasesCaves(caves.getSize(), false);
        for (int i = 0; i < caves.getSize(); ++i) {
            upperCasesCaves[i] = string::isUpperCaseString(caves.getString(i));
        }

        int start = caves.getIndex("start");
        int end = caves.getIndex("end");

        struct history {
            history(int size) {
                h = std::vector<int>(size, 0);
            }
            void add(int index) {
                h[index]++;
                path.push_back(index);
            }
            std::vector<int> h;
            std::vector<int> path;
        };

        for (int i = 0; i < caves.getSize(); ++i) {
            if (map[start][i]) {
                history h(caves.getSize());
                h.add(start);
                h.add(i);
                std::vector<history> paths{h};
                while (!paths.empty()) {
                    std::vector<history> newPaths;
                    for (const auto& p : paths) {
                        for (int j = 0; j < caves.getSize(); ++j) {
                            if (map[p.path.back()][j]) {
                                if (j == end) {
                                    sol++;
                                }
                                else if (upperCasesCaves[j]) {
                                    history h1 = p;
                                    h1.add(j);
                                    newPaths.push_back(h1);
                                }
                                else if (j != start) {
                                    history h1 = p;
                                    if (p.h[j] == 0) {
                                        h1.add(j);
                                        newPaths.push_back(h1);
                                    }
                                }
                            }
                        }
                    }
                    paths = newPaths;
                }
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        stringtointmap::StringToIntMap caves;
        int sol = 0;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "-");
            caves.addString(tokens[0]);
            caves.addString(tokens[1]);
        }

        std::vector<std::vector<bool>> map(caves.getSize(), std::vector<bool>(caves.getSize(), false));
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "-");
            map[caves.getIndex(tokens[0])][caves.getIndex(tokens[1])] = true;
            map[caves.getIndex(tokens[1])][caves.getIndex(tokens[0])] = true;
        }
        std::vector<bool> upperCasesCaves(caves.getSize(), false);
        for (int i = 0; i < caves.getSize(); ++i) {
            upperCasesCaves[i] = string::isUpperCaseString(caves.getString(i));
        }

        int start = caves.getIndex("start");
        int end = caves.getIndex("end");

        struct history {
            history(int size, bool small = false) {
                h = std::vector<int>(size, 0);
                smallCaveVisitedTwice = small;
            }
            void add(int index) {
                h[index]++;
                path.push_back(index);
            }
            std::vector<int> h;
            std::vector<int> path;
            bool smallCaveVisitedTwice;
        };

        for (int i = 0; i < caves.getSize(); ++i) {
            if (map[start][i]) {
                history h(caves.getSize());
                h.add(start);
                h.add(i);
                std::vector<history> paths{h};
                while (!paths.empty()) {
                    std::vector<history> newPaths;
                    for (const auto& p : paths) {
                        for (int j = 0; j < caves.getSize(); ++j) {
                            if (map[p.path.back()][j]) {
                                if (j == end) {
                                    sol++;
                                }
                                else if (upperCasesCaves[j]) {
                                    history h1 = p;
                                    h1.add(j);
                                    newPaths.push_back(h1);
                                }
                                else if (j != start) {
                                    history h1 = p;
                                    if (p.h[j] == 0) {
                                        h1.add(j);
                                        newPaths.push_back(h1);
                                    }
                                    else if (p.h[j] == 1 && !p.smallCaveVisitedTwice) {
                                        h1.add(j);
                                        h1.smallCaveVisitedTwice = true;
                                        newPaths.push_back(h1);
                                    }
                                }
                            }
                        }
                    }
                    paths = newPaths;
                }
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day12::part_1("../2021/day12/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day12::part_2("../2021/day12/input.in") << std::endl;

    return 0;
}
#endif
