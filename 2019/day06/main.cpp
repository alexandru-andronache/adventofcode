#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <deque>

namespace aoc2019_day06 {
    int current_head = 0;
    std::deque<int> lookup;
    int min = std::numeric_limits<int>::max();

    int getId(std::map<std::string, int>& objectsId, std::string object) {
        auto it = objectsId.find(object);
        if (it != objectsId.end()) {
            return it->second;
        }
        objectsId[object] = objectsId.size();
        return objectsId[object];
    }

    void solution2(const std::vector<std::vector<bool>>& v, int n, int finish) {
        current_head++;
        int p = lookup.back();
        for (int i = 0; i < n; ++i) {
            if ((v[p][i] == 1) || (v[i][p] == 1)) {
                auto it = std::find(lookup.begin(), lookup.end(), i);
                if (it == lookup.end()) {
                    if (i == finish) {
                        min = std::min(min, current_head);
                    }
                    lookup.push_back(i);
                    solution2(v, n, finish);
                }
            }
        }
        current_head--;
        lookup.pop_back();
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::map<std::string, int> objectsId;
        std::vector<std::vector<bool>> v(2000, std::vector<bool>(2000, false));

        for (const auto& line : lines) {
            std::vector<std::string> objects = utils::splitString(line, ")");
            v[getId(objectsId, objects[0])][getId(objectsId, objects[1])] = true;
        }

        int sol = 0;
        for (int i = 0; i < objectsId.size(); ++i) {
            for (int j = 0; j < objectsId.size(); ++j) {
                if (v[i][j] == 1) {
                    sol++;
                    std::deque<int> head;
                    head.push_back(i);
                    while (head.size() > 0) {
                        int x = head.back();
                        for (int k = 0; k < objectsId.size(); ++k) {
                            if (v[k][x] == 1) {
                                head.push_front(k);
                                sol++;
                            }
                        }
                        head.pop_back();
                    }
                }
            }
        }
        return sol;
    }

    int part_2(std::string_view path, const std::string& begin = "YOU", const std::string& end = "SAN") {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::map<std::string, int> objectsId;
        std::vector<std::vector<bool>> v(2000, std::vector<bool>(2000, false));

        for (const auto& line : lines) {
            std::vector<std::string> objects = utils::splitString(line, ")");
            v[getId(objectsId, objects[0])][getId(objectsId, objects[1])] = true;
        }

        int start = objectsId.find(begin)->second;
        int finish = objectsId.find(end)->second;

        current_head = 0;
        lookup.clear();
        min = std::numeric_limits<int>::max();
        lookup.push_back(start);
        solution2(v, objectsId.size(), finish);
        return min - 2;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day06::part_1("../2019/day06/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day06::part_2("../2019/day06/input.in") << std::endl;

    return 0;
}
#endif
