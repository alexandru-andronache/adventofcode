#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day12 {
    bool isValid(std::string str, const std::vector<int>& v) {
        int j = 0, nr = v[0], valid = true;
        int i = 0;
        bool vectorIsDone = false;
        while (i < str.size() && valid) {
            bool foundStr = false;
            while (i < str.size() && str[i] == '#') {
                if (vectorIsDone) {
                    valid = false;
                }
                nr--;
                i++;
                foundStr = true;
            }
            if (foundStr) {
                if (nr != 0) {
                    valid = false;
                }
                j++;
                if (j < v.size()) {
                    nr = v[j];
                }
                else {
                    vectorIsDone = true;
                }
            }
            i++;
        }
        valid = valid & vectorIsDone;
        return valid;
    }

    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sol = 0;
        for (int index = 0; const auto& line : input) {
            std::vector<std::string> t = utils::splitString(line, " ,");
            std::vector<int> v;
            for (int i = 1; i < t.size(); ++i) {
                v.push_back(std::stoi(t[i]));
            }

            std::string p = t[0];
            int nr = 0;
            for (int i = 0; i < p.size(); ++i) {
                if (p[i] == '?') nr++;
            }

            int maxValue = 0;
            std::bitset<16> perm(maxValue);
//            std::cout << p << std::endl;
            while (maxValue <= (std::pow(2, nr) - 1)) {
                std::bitset<31> perm(maxValue);
                std::string x;
                int j = 0;
                for (int i = 0; i < p.size(); ++i) {
                    if (p[i] != '?') x += p[i];
                    else if (perm[j] == 0) x += '.', j++;
                    else x += '#', j++;
                }

                if (isValid(x, v)) {
                    sol++;
                }
                maxValue++;
            }

            index++;
        }
        return sol;
    }

    unsigned long long solve(std::string str, const std::vector<int>& v) {
        // current position, number of groups in v, count of # in the current group

        int maxElement = *std::max_element(v.begin(), v.end());

        unsigned long long solutions[140][40][140];
        for (int i = 0; i < 140; ++i) {
            for (int j = 0; j < 40; ++j) {
                for (int  k = 0; k < 140; ++k) {
                    solutions[i][j][k] = 0;
                }
            }
        }
        solutions[0][0][0] = 1;

        for (int i = 0; i < str.size(); ++i) {
            for (int j = 0; j < v.size(); ++j) {
                for (int k = 0; k < str.size() + 1; ++k) {
                    if (solutions[i][j][k] != 0) {
                        if (str[i] == '.' || str[i] == '?') {
                            if (k == 0 || (j > 0 && k == v[j - 1])) {
                                solutions[i + 1][j][0] += solutions[i][j][k];
//                                std::cout << "case . " << i << " " << j << " " << k << " " << solutions[i + 1][j][0] << std::endl;
                            }
                        }
                        if (str[i] == '#' || str[i] == '?') {
                            if (k == 0) {
                                solutions[i + 1][j + 1][k + 1] += solutions[i][j][k];
//                                std::cout << "case # " << i << " " << j << " " << k << solutions[i + 1][j + 1][k + 1] << std::endl;
                            }
                            else {
                                solutions[i + 1][j][k + 1] += solutions[i][j][k];
                            }

                        }
                    }
                }
            }
        }

        unsigned long long value = solutions[str.size()][v.size() - 1][0];
        return value;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        unsigned long long sol = 0;
        for (const auto& line : input) {
            std::vector<std::string> t = utils::splitString(line, " ,");
            std::vector<int> v;
            for (int j = 0; j < 5; ++j) {
                for (int i = 1; i < t.size(); ++i) {
                    v.push_back(std::stoi(t[i]));
                }
            }

            std::string p;
            for (int i = 0; i < 5; ++i) {
                p += t[0];
                if (i != 4) {
                    p += '?';
                }
                else {
                    p += '.';
                }
            }
            v.push_back(p.size() + 1);

            sol += solve(p, v);
        }
        return sol;
    }
}

#ifdef TESTING
TEST(Tests2023Day12, part_1_test) {
    ASSERT_EQ(aoc2023_day12::part_1("../2023/day12/input_test.in"), 21);
}

TEST(Tests2023Day12, part_1_real_test) {
    ASSERT_EQ(aoc2023_day12::part_1("../2023/day12/input.in"), 8270);
}

TEST(Tests2023Day12, part_2_test) {
    ASSERT_EQ(aoc2023_day12::part_2("../2023/day12/input_test.in"), 525152);
}

TEST(Tests2023Day12, part_2_real_test) {
    ASSERT_EQ(aoc2023_day12::part_2("../2023/day12/input.in"), 204640299929836);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day12::part_1("../2023/day12/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day12::part_2("../2023/day12/input.in") << std::endl;

    return 0;
}
#endif
