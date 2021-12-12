#include "file.h"
#include "utilities.h"
#include "StringToIntMap.h"
#include "string_util.h"
#include <iostream>
#include <vector>
#include <map>

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
            history(const std::vector<int>& his) {
                h = his;
            }
            history(std::vector<int>& his) {
                h = his;
            }
            std::vector<int> h;
        };

        for (int i = 0; i < caves.getSize(); ++i) {
            if (map[start][i]) {
                std::vector<history> paths {{{start, i}}};
                while (!paths.empty()) {
                    std::vector<history> newPaths;
                    for (const auto& p : paths) {
                        for (int j = 0; j < 30; ++j) {
                            if (map[p.h.back()][j]) {
                                if (j == end) {
                                    sol++;
                                }
                                else if (j == start) {

                                }
                                else if (upperCasesCaves[j]) {
                                    std::vector<int> temp = p.h;
                                    temp.push_back(j);
                                    newPaths.push_back(temp);
                                }
                                else {
                                    std::vector<int> temp = p.h;
                                    if (std::find(temp.begin(), temp.end(), j) == temp.end()) {
                                        temp.push_back(j);
                                        newPaths.push_back(temp);
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
            history(const std::vector<int>& his, bool small) {
                h = his;
                smallCaveVisitedTwice = small;
            }
            history(std::vector<int>& his, bool small) {
                h = his;
                smallCaveVisitedTwice = small;
            }
            std::vector<int> h;
            bool smallCaveVisitedTwice;
        };

        for (int i = 0; i < caves.getSize(); ++i) {
            if (map[start][i]) {
                std::vector<history> paths {{{start, i}, false}};
                while (!paths.empty()) {
                    std::vector<history> newPaths;
                    for (const auto& p : paths) {
                        for (int j = 0; j < 30; ++j) {
                            if (map[p.h.back()][j]) {
                                if (j == end) {
                                    sol++;
                                }
                                else if (j == start) {

                                }
                                else if (upperCasesCaves[j]) {
                                    std::vector<int> temp = p.h;
                                    temp.push_back(j);
                                    newPaths.push_back({temp, p.smallCaveVisitedTwice});
                                }
                                else {
                                    std::vector<int> temp = p.h;
                                    if (std::find(temp.begin(), temp.end(), j) == temp.end()) {
                                        temp.push_back(j);
                                        newPaths.push_back({temp, p.smallCaveVisitedTwice});
                                    }
                                    else if (std::count(temp.begin(), temp.end(), j) == 1 && !p.smallCaveVisitedTwice) {
                                        temp.push_back(j);
                                        newPaths.push_back({temp, true});
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
