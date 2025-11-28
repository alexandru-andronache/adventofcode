#include "file.h"
#include "utilities.h"
#include <map>
#include <ranges>
#include <utility>
#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoccodes_2025_day09 {

    struct relation {
        int child;
        int parent1;
        int parent2;
    };

    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        std::vector<int> child{0, 1, 2};
        std::vector<int> parents{0, 1, 2};
        int i = 2;
        while (i < lines[0].size() && child.size() > 1) {
            if (lines[0][i] == lines[1][i] && lines[2][i] != lines[0][i]) {
                child.erase(std::ranges::remove(child, 2).begin(), child.end());
            }
            if (lines[1][i] == lines[2][i] && lines[0][i] != lines[1][i]) {
                child.erase(std::ranges::remove(child, 0).begin(), child.end());
            }
            if (lines[0][i] == lines[2][i] && lines[1][i] != lines[0][i]) {
                child.erase(std::ranges::remove(child, 1).begin(), child.end());
            }
            i++;
        }
        parents.erase(std::ranges::remove(parents, child.front()).begin(), parents.end());

        int sol1 = 0, sol2 = 0;
        for (int i = 2; i < lines[0].size(); ++i) {
            if (lines[child.front()][i] == lines[parents[0]][i]) {
                sol1++;
            }
            if (lines[child.front()][i] == lines[parents[1]][i]) {
                sol2++;
            }
        }
        return sol1 * sol2;
    }

    int calculate(const std::vector<std::string>& dna,
                  int index_i,
                  int index_j,
                  int index_k,
                  std::vector<std::vector<bool>>& childrens,
                  std::vector<std::vector<bool>>& parents_relations) {
        std::vector<int> child{index_i, index_j, index_k};
        std::vector<int> parents{index_i, index_j, index_k};
        // std::vector<std::string> lines{std::string(a), std::string(b), std::string(c)};
        for (int i = 0; i < dna[index_i].size(); ++i) {
            if (dna[index_i][i] == dna[index_j][i] && dna[index_k][i] != dna[index_i][i]) {
                child.erase(std::ranges::remove(child, index_k).begin(), child.end());
            }
            if (dna[index_j][i] == dna[index_k][i] && dna[index_i][i] != dna[index_j][i]) {
                child.erase(std::ranges::remove(child, index_i).begin(), child.end());
            }
            if (dna[index_i][i] == dna[index_k][i] && dna[index_j][i] != dna[index_i][i]) {
                child.erase(std::ranges::remove(child, index_j).begin(), child.end());
            }
        }
        if (child.size() != 1) {
            return 0;
        }
        parents.erase(std::ranges::remove(parents, child.front()).begin(), parents.end());
        for (int i = 0; i < childrens.size(); ++i) {
            if (childrens[child[0]][i]) {
                return 0;
            }
        }

        if (parents_relations[child[0]][parents[0]]) {
            return 0;
        }
        if (parents_relations[child[0]][parents[1]]) {
            return 0;
        }

        parents_relations[parents[0]][parents[1]] = true;
        childrens[child[0]][parents[0]] = true;
        childrens[child[0]][parents[1]] = true;


        int sol1 = 0, sol2 = 0;
        for (int i = 0; i < dna[child.front()].size(); ++i) {
            if (dna[child.front()][i] == dna[parents[0]][i]) {
                sol1++;
            }
            if (dna[child.front()][i] == dna[parents[1]][i]) {
                sol2++;
            }
        }
        return sol1 * sol2;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::string> dna;
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ": ");
            dna.push_back(tokens[1]);
        }
        std::vector<std::vector<bool>> childrens(dna.size(), std::vector<bool>(dna.size(), false));
        std::vector<std::vector<bool>> parents(dna.size(), std::vector<bool>(dna.size(), false));

        unsigned long long sum = 0;
        for (int i = 0; i < dna.size(); ++i) {
            for (int j = i + 1; j < dna.size(); ++j) {
                for (int k = j + 1; k < dna.size(); ++k) {
                    sum += calculate(dna, i, j, k, childrens, parents);
                }
            }
        }

        return sum;
    }

    unsigned long long part_3(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::string> dna;
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ": ");
            dna.push_back(tokens[1]);
        }
        std::vector<std::vector<bool>> childrens(dna.size(), std::vector<bool>(dna.size(), false));
        std::vector<std::vector<bool>> parents(dna.size(), std::vector<bool>(dna.size(), false));

        for (int i = 0; i < dna.size(); ++i) {
            for (int j = i + 1; j < dna.size(); ++j) {
                for (int k = j + 1; k < dna.size(); ++k) {
                    calculate(dna, i, j, k, childrens, parents);
                }
            }
        }

        std::vector<bool> visited(dna.size(), false);
        int max = 0;
        for (int i = 0; i < dna.size(); ++i) {
            std::vector<int> family;
            if (!visited[i]) {
                family.push_back(i);
                visited[i] = true;
                for (int j = 0; j < family.size(); ++j) {
                    for (int k = 0; k < dna.size(); ++k) {
                        if (!visited[k] && (childrens[family[j]][k] || childrens[family[j]][k])) {
                            family.push_back(k);
                            visited[k] = true;
                        }
                    }
                    for (int k = 0; k < dna.size(); ++k) {
                        if (!visited[k] && (parents[family[j]][k])) {
                            family.push_back(k);
                            visited[k] = true;
                        }
                    }
                }
                max = std::max(max, static_cast<int>(family.size()));
            }
        }

        return max;
    }
}

#ifdef TESTING
namespace aoccodes_2025_day09 {
    TEST(Testscodes_2025Day09, part_1_test) {
        ASSERT_EQ(part_1("../codes_2025/day09/input/input_part_1_test.in"), 414);
    }

    TEST(Testscodes_2025Day09, part_1_real_test) {
        ASSERT_EQ(part_1("../codes_2025/day09/input/input_part_1.in"), 6480);
    }

    TEST(Testscodes_2025Day09, part_2_test) {
        ASSERT_EQ(part_2("../codes_2025/day09/input/input_part_2_test.in"), 1245);
    }

    TEST(Testscodes_2025Day09, part_2_real_test) {
        ASSERT_EQ(part_2("../codes_2025/day09/input/input_part_2.in"), 322970);
    }

    TEST(Testscodes_2025Day09, part_3_test) {
        ASSERT_EQ(part_3("../codes_2025/day09/input/input_part_3_test.in"), 12);
    }

    TEST(Testscodes_2025Day09, part_3_test_2) {
        ASSERT_EQ(part_3("../codes_2025/day09/input/input_part_3_test_2.in"), 36);
    }

    // TEST(Testscodes_2025Day09, part_3_real_test) {
    //     ASSERT_EQ(part_3("../codes_2025/day09/input/input_part_3.in"), 0);
    // }
}
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoccodes_2025_day09::part_1("../codes_2025/day09/input/input_part_1.in"));
    fmt::print("Part 2: {}\n", aoccodes_2025_day09::part_2("../codes_2025/day09/input/input_part_2.in"));
    fmt::print("Part 3: {}\n", aoccodes_2025_day09::part_3("../codes_2025/day09/input/input_part_3.in"));

    return 0;
}
#endif
