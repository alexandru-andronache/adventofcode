#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day19 {
    struct tree {
        std::string key;
        int value;
        char comp;
        tree* left;
        tree* right;
    };

    tree* createTree(std::string str, int& i) {
        tree* root = new tree();
        while (i < str.size() && ((str[i] >= 'a' && str[i] <= 'z') || str[i] == 'A' || str[i] == 'R')) {
            root->key += str[i];
            i++;
        }
        if (str[i] == '<' || str[i] == '>') {
            root->comp = str[i];
        }
        else {
            root->comp = ' ';
        }
        i++;
        if (root->comp != ' ') {
            root->value = 0;
            while (i < str.size() && str[i] >= '0' && str[i] <= '9') {
                root->value = root->value * 10 + str[i] - '0';
                i++;
            }
        }
        if (str[i] == ':') {
            i++;
            root->left = createTree(str, i);
            root->right = createTree(str, i);
        }
        return root;
    }

    unsigned long long part_1(std::string_view path) {
        std::vector<tree*> nodes;

        unsigned long long sol = 0;
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<std::string, int> initial;
        int start = 0;
        for (int k = 0; k < input.size(); ++k) {
            if (input[k] == "") {
                start = k + 1;
            }
            if (start == 0) {
                std::vector<std::string> t = utils::splitString(input[k], "{}");
                initial[t[0]] = k;
                std::string str = t[1];
                int i = 0;
                nodes.push_back(createTree(str, i));
            }
        }

        for (int k = start; k < input.size(); ++k) {
            std::vector<std::string> t = utils::splitString(input[k], "{}=,");
            std::map<std::string, int> values;
            unsigned long long sum = 0;
            for (int i = 0; i < t.size(); i += 2) {
                values[t[i]] = std::stoi(t[i + 1]);
                sum += std::stoi(t[i + 1]);
            }
            int current = initial["in"];
            while (true) {
                tree* r = nodes[current];
                while (r->comp != ' ') {
                    if (r->comp == '<') {
                        if (values[r->key] < r->value) {
                            r = r->left;
                        }
                        else {
                            r = r->right;
                        }
                    }
                    else {
                        if (values[r->key] > r->value) {
                            r = r->left;
                        }
                        else {
                            r = r->right;
                        }
                    }
                }
                if (r->key == "A" || r->key == "R") {
                    if (r->key == "A") {
                        sol += sum;
                    }
                    break;
                }
                else {
                    current = initial[r->key];
                }
            }
        }
        return sol;
    }

    void solve_part_2(std::pair<unsigned long long, unsigned long long> x, std::pair<unsigned long long, unsigned long long> m, std::pair<unsigned long long, unsigned long long> a,
                                    std::pair<unsigned long long, unsigned long long> s, const std::vector<tree*>& nodes, const std::map<std::string, int>& initial,
                                    tree* r, unsigned long long& sum) {
        if (r->comp != ' ') {
            if (r->comp == '<') {
                if (r->key == "x") {
                    solve_part_2({x.first, r->value - 1}, m, a, s, nodes, initial, r->left, sum);
                    solve_part_2({r->value, x.second}, m, a, s, nodes, initial, r->right, sum);
                }
                else if (r->key == "m") {
                    solve_part_2(x, {m.first, r->value - 1}, a, s, nodes, initial, r->left, sum);
                    solve_part_2(x, {r->value, m.second}, a, s, nodes, initial, r->right, sum);
                }
                else if (r->key == "a") {
                    solve_part_2(x, m, {a.first, r->value - 1}, s, nodes, initial, r->left, sum);
                    solve_part_2(x, m, {r->value, a.second}, s, nodes, initial, r->right, sum);
                }
                else if (r->key == "s") {
                    solve_part_2(x, m, a, {s.first, r->value - 1}, nodes, initial, r->left, sum);
                    solve_part_2(x, m, a, {r->value, s.second}, nodes, initial, r->right, sum);
                }
            }
            else {
                if (r->key == "x") {
                    solve_part_2({x.first, r->value}, m, a, s, nodes, initial, r->right, sum);
                    solve_part_2({r->value + 1, x.second}, m, a, s, nodes, initial, r->left, sum);
                }
                else if (r->key == "m") {
                    solve_part_2(x, {m.first, r->value}, a, s, nodes, initial, r->right, sum);
                    solve_part_2(x, {r->value + 1, m.second}, a, s, nodes, initial, r->left, sum);
                }
                else if (r->key == "a") {
                    solve_part_2(x, m, {a.first, r->value}, s, nodes, initial, r->right, sum);
                    solve_part_2(x, m, {r->value + 1, a.second}, s, nodes, initial, r->left, sum);
                }
                else if (r->key == "s") {
                    solve_part_2(x, m, a, {s.first, r->value}, nodes, initial, r->right, sum);
                    solve_part_2(x, m, a, {r->value + 1, s.second}, nodes, initial, r->left, sum);
                }
            }
        }
        else {
            if (r->key == "A" || r->key == "R") {
                if (r->key == "A") {
                    sum += (x.second - x.first + 1) * (m.second - m.first + 1) * (a.second - a.first + 1) *
                             (s.second - s.first + 1);
                }
                return;
            } else {
                solve_part_2(x, m, a, s, nodes, initial, nodes[initial.at(r->key)], sum);
            }
        }
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<tree*> nodes;

        unsigned long long sol = 0;
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<std::string, int> initial;
        std::map<char, std::pair<unsigned long long, unsigned long long>> pairs {{'x', {1, 4000}}, {'m', {1, 4000}}, {'a', {1, 4000}}, {'s', {1, 4000}}};
        int start = 0;
        for (int k = 0; k < input.size(); ++k) {
            if (input[k] == "") {
                start = k + 1;
            }
            if (start == 0) {
                std::vector<std::string> t = utils::splitString(input[k], "{}");
                initial[t[0]] = k;
                std::string str = t[1];
                int i = 0;
                nodes.push_back(createTree(str, i));
            }
        }

        solve_part_2({1, 4000}, {1, 4000}, {1, 4000}, {1, 4000}, nodes, initial, nodes[initial["in"]], sol);

        return sol;
    }
}

#ifdef TESTING
TEST(Tests2023Day19, part_1_test) {
    ASSERT_EQ(aoc2023_day19::part_1("../2023/day19/input_test.in"), 19114);
}

TEST(Tests2023Day19, part_1_real_test) {
    ASSERT_EQ(aoc2023_day19::part_1("../2023/day19/input.in"), 373302);
}

TEST(Tests2023Day19, part_2_test) {
    ASSERT_EQ(aoc2023_day19::part_2("../2023/day19/input_test.in"), 167409079868000);
}

TEST(Tests2023Day19, part_2_real_test) {
    ASSERT_EQ(aoc2023_day19::part_2("../2023/day19/input.in"), 130262715574114);
}
#endif

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day19::part_1("../2023/day19/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day19::part_2("../2023/day19/input.in") << std::endl;

    return 0;
}
#endif
