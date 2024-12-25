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
    std::vector<std::vector<int>> neighbours;
    std::map<int, std::string> computers_reverse;
    int max = 0;
    std::string solution;

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::map<std::string, int> computers;
        std::vector<std::vector<bool>> connections(600, std::vector<bool>(600, false));
        int index = 0;
        int sol = 0;

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "-");
            for (const auto& token : tokens) {
                if (!computers.contains(token)) {
                    computers[token] = index++;
                    computers_reverse[index - 1] = token;
                    neighbours.emplace_back();
                }
            }
            connections[computers[tokens[0]]][computers[tokens[1]]] = true;
            connections[computers[tokens[1]]][computers[tokens[0]]] = true;
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

    // https://en.wikipedia.org/wiki/Bron%E2%80%93Kerbosch_algorithm
    void BronKerbosch(const std::set<int>& R, std::set<int> P, std::set<int> X) {
        if (P.empty() && X.empty() && R.size() > max) {
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
        std::set<int> copy_P_X = P;
        copy_P_X.insert(X.begin(), X.end());
        int x = *copy_P_X.begin();
        std::set<int> P_without_neighbours_x = P;
        for (const auto& n : neighbours[x]) {
            if (P.contains(n)) {
                P_without_neighbours_x.erase(n);
            }
        }
        for (const auto& v : P_without_neighbours_x) {
            std::set<int> new_X;
            std::set<int> new_R = R;
            std::set<int> new_P;
            new_R.insert(v);
            for (const auto& n : neighbours[v]) {
                if (P.contains(n)) {
                    new_P.insert(n);
                }
                if (X.contains(n)) {
                    new_X.insert(n);
                }
            }
            BronKerbosch(new_R, new_P, new_X);
            P.erase(v);
            X.insert(v);
        }
    }

    std::string part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::map<std::string, int> computers;
        neighbours.clear();

        int index = 0;
        solution = "";
        computers_reverse.clear();

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, "-");
            for (const auto& token : tokens) {
                if (!computers.contains(token)) {
                    computers[token] = index++;
                    computers_reverse[index - 1] = token;
                    neighbours.emplace_back();
                }
            }
            neighbours[computers[tokens[0]]].push_back(computers[tokens[1]]);
            neighbours[computers[tokens[1]]].push_back(computers[tokens[0]]);
        }

        std::set<int> P;
        for (int i = 0; i < index; ++i) {
            P.insert(i);
        }
        BronKerbosch({}, P, {});
        return solution;
    }
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
