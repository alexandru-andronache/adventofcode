#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <set>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2024_day23 {
    std::set<int> group;
    std::vector<std::vector<bool>> connections(600, std::vector<bool>(600, false));
    std::vector<std::vector<int>> neighbours;
    std::map<int, std::string> computers_reverse;
    int max = 0;
    std::string solution;

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::map<std::string, int> computers;
        std::map<int, std::string> computers_reverse;
        std::vector<std::vector<bool>> connections(600, std::vector<bool>(600, false));
        std::vector<bool> visited(600, false);
        int index = 0;
        int sol = 0;
        std::vector<std::pair<int, int>> pairs;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "-");
            if (!computers.contains(tokens[0])) {
                computers[tokens[0]] = index++;
                computers_reverse[index - 1] = tokens[0];
            }
            if (!computers.contains(tokens[1])) {
                computers[tokens[1]] = index++;
                computers_reverse[index - 1] = tokens[1];
            }
            connections[computers[tokens[0]]][computers[tokens[1]]] = true;
            connections[computers[tokens[1]]][computers[tokens[0]]] = true;
            pairs.emplace_back(computers[tokens[0]], computers[tokens[1]]);
        }

        for (int i = 0; i < index; ++i) {
            for (int j = i + 1; j < index; ++j) {
                if (connections[i][j]) {
                    for (int k = j + 1; k < index; ++k) {
                        if (connections[j][k] && connections[k][i]) {
                            if (computers_reverse[i].starts_with("t") ||
                                computers_reverse[j].starts_with("t") ||
                                computers_reverse[k].starts_with("t")) {
                                sol++;
                                }
                        }
                    }
                }
            }
        }
        return sol;
    }

    void BronKerbosch(std::set<int> R, std::set<int> P, std::set<int> X) {
        if (P.empty() && X.empty()) {
            if (R.size() > max) {
                max = R.size();
                std::vector<std::string> computers;
                for (const auto& g: R) {
                    computers.push_back(computers_reverse[g]);
                }
                std::ranges::sort(computers);
                solution = computers[0];
                for (int j = 1; j < computers.size(); ++j) {
                    solution += "," + computers[j];
                }
            }
        }
        std::set<int> copy_P = P;
        for (const auto& v : P) {
            std::set<int> new_X;
            std::set<int> new_R = R;
            std::set<int> new_P;
            new_R.insert(v);
            for (const auto& n : neighbours[v]) {
                if (copy_P.contains(n)) {
                    new_P.insert(n);
                }
                if (X.contains(n)) {
                    new_X.insert(n);
                }
            }
            BronKerbosch(new_R, new_P, new_X);
            copy_P.erase(v);
            X.insert(v);
        }
    }

    // https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
    std::string part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::map<std::string, int> computers;
        neighbours.clear();

        std::vector<bool> visited(600, false);
        int index = 0;
        int sol = 0;
        solution = "";
        computers_reverse.clear();

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "-");
            if (!computers.contains(tokens[0])) {
                computers[tokens[0]] = index++;
                computers_reverse[index - 1] = tokens[0];
                neighbours.emplace_back();
            }
            if (!computers.contains(tokens[1])) {
                computers[tokens[1]] = index++;
                computers_reverse[index - 1] = tokens[1];
                neighbours.emplace_back();
            }
            neighbours[computers[tokens[0]]].push_back(computers[tokens[1]]);
            neighbours[computers[tokens[1]]].push_back(computers[tokens[0]]);
            connections[computers[tokens[0]]][computers[tokens[1]]] = true;
            connections[computers[tokens[1]]][computers[tokens[0]]] = true;
        }

        std::set<int> P;
        for (int i = 0; i < index; ++i) {
            P.insert(i);
        }
        BronKerbosch({}, P, {});
        return solution;
    }



    // void solve_part_2(int start, int index) {
    //     for (int i = start; i < index; ++i) {
    //         if (!group.contains(i)) {
    //             bool connected = true;
    //             for (const auto& g : group) {
    //                 if (!connections[g][i]) {
    //                     connected = false;
    //                 }
    //             }
    //             if (connected) {
    //                 group.insert(i);
    //                 if (group.size() > max) {
    //                     max = group.size();
    //                     std::vector<std::string> computers;
    //                     for (const auto& g: group) {
    //                         computers.push_back(computers_reverse[g]);
    //                     }
    //                     std::ranges::sort(computers);
    //                     solution = computers[0];
    //                     for (int j = 1; j < computers.size(); ++j) {
    //                         solution += "," + computers[j];
    //                     }
    //                 }
    //                 solve_part_2(i + 1, index);
    //                 group.erase(i);
    //             }
    //         }
    //     }
    // }

    // std::string part_2(std::string_view path) {
    //     std::vector<std::string> lines = file::readFileAsArrayString(path);
    //     std::vector<std::vector<int>> neighbours;
    //     std::map<std::string, int> computers;
    //
    //     std::vector<bool> visited(600, false);
    //     int index = 0;
    //     int sol = 0;
    //     solution = "";
    //     computers_reverse.clear();
    //
    //     for (const auto& line : lines) {
    //         std::vector<std::string> tokens = utils::splitString(line, "-");
    //         if (!computers.contains(tokens[0])) {
    //             computers[tokens[0]] = index++;
    //             computers_reverse[index - 1] = tokens[0];
    //         }
    //         if (!computers.contains(tokens[1])) {
    //             computers[tokens[1]] = index++;
    //             computers_reverse[index - 1] = tokens[1];
    //         }
    //         connections[computers[tokens[0]]][computers[tokens[1]]] = true;
    //         connections[computers[tokens[1]]][computers[tokens[0]]] = true;
    //     }
    //
    //     solve_part_2(0, index);
    //
    //     return solution;
    // }
}

#ifdef TESTING
namespace aoc2024_day23 {
    TEST(Tests2024Day23, part_1_test) {
        ASSERT_EQ(part_1("../2024/day23/input_test.in"), 7);
    }

    TEST(Tests2024Day23, part_1_real_test) {
        ASSERT_EQ(part_1("../2024/day23/input.in"), 1327);
    }

    TEST(Tests2024Day23, part_2_test) {
        ASSERT_EQ(part_2("../2024/day23/input_test.in"), "co,de,ka,ta");
    }

    TEST(Tests2024Day23, part_2_real_test) {
        ASSERT_EQ(part_2("../2024/day23/input.in"), "df,kg,la,mp,pb,qh,sk,th,vn,ww,xp,yp,zk");
    }
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2024_day23::part_1("../2024/day23/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2024_day23::part_2("../2024/day23/input.in") << std::endl;

    return 0;
}
#endif
