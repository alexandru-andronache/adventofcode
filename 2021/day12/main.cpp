#include "file.h"
#include "utilities.h"
#include "StringToIntMap.h"
#include <iostream>
#include <vector>
#include <map>

namespace aoc2021_day12 {
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        stringtointmap::StringToIntMap caves;
        int sol = 0;
        std::vector<std::vector<bool>> map(30, std::vector<bool>(30, false));
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "-");
            caves.addString(tokens[0]);
            caves.addString(tokens[1]);
            map[caves.getIndex(tokens[0])][caves.getIndex(tokens[1])] = true;
            map[caves.getIndex(tokens[1])][caves.getIndex(tokens[0])] = true;
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

        for (int i = 0; i < 30; ++i) {
            if (map[start][i]) {
                std::vector<history> paths {{{start, i}}};
                while (!paths.empty()) {
                    std::vector<history> newPaths;
                    for (const auto& p : paths) {
                        for (int j = 0; j < 30; ++j) {
                            if (map[p.h.back()][j]) {
                                std::string cave = caves.getString(j);
                                bool allUpperCase = true;
                                for (const auto& c : cave) {
                                    if (c >= 'a' && c <= 'z') {
                                        allUpperCase = false;
                                    }
                                }
                                if (j == end) {
                                    sol++;
                                }
                                else if (j == start) {

                                }
                                else if (allUpperCase) {
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
        int sol = 0;
        std::vector<std::vector<bool>> map(30, std::vector<bool>(30, false));
        std::map<std::string, int> caves;
        std::map<int, std::string> cavesReverse;
        int index = 0;
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "-");
            if (caves.find(tokens[0]) == caves.end()) {
                caves.insert({tokens[0], index});
                cavesReverse.insert({index, tokens[0]});
                index++;
            }
            if (caves.find(tokens[1]) == caves.end()) {
                caves.insert({tokens[1], index});
                cavesReverse.insert({index, tokens[1]});

                index++;
            }
            map[caves[tokens[0]]][caves[tokens[1]]] = true;
            map[caves[tokens[1]]][caves[tokens[0]]] = true;
        }

        int start = caves["start"];
        int end = caves["end"];

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

        for (int i = 0; i < 30; ++i) {
            if (map[start][i]) {
                std::vector<history> paths {{{start, i}, false}};
                while (!paths.empty()) {
                    std::vector<history> newPaths;
                    for (const auto& p : paths) {
                        for (int j = 0; j < 30; ++j) {
                            if (map[p.h.back()][j]) {
                                std::string cave = cavesReverse[j];
                                bool allUpperCase = true;
                                for (const auto& c : cave) {
                                    if (c >= 'a' && c <= 'z') {
                                        allUpperCase = false;
                                    }
                                }
                                if (j == end) {
                                    sol++;
                                }
                                else if (j == start) {

                                }
                                else if (allUpperCase) {
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
