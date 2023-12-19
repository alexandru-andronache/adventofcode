#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

typedef unsigned long long ull;

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

    ull part_1(std::string_view path) {
        std::vector<tree*> nodes;

        ull sol = 0;
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
                    if ((r->comp == '<' && values[r->key] < r->value) || (r->comp == '>' && values[r->key] > r->value)) {
                        r = r->left;
                    }
                    else {
                        r = r->right;
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

    ull solve_part_2(const std::map<std::string, std::pair<ull, ull>>& ranges,
                     const std::vector<tree*>& nodes,
                     const std::map<std::string, int>& initial,
                     tree* root) {
        ull sum = 0;
        if (root->comp != ' ') {
            std::map<std::string, std::pair<ull, ull>> rangesLeft = ranges;
            std::map<std::string, std::pair<ull, ull>> rangesRight = ranges;
            if (root->comp == '<') {
                rangesLeft.at(root->key) = {rangesLeft.at(root->key).first, root->value - 1};
                rangesRight.at(root->key) = {root->value, rangesRight.at(root->key).second};
                sum += solve_part_2(rangesLeft, nodes, initial, root->left);
                sum += solve_part_2(rangesRight, nodes, initial, root->right);
            }
            else {
                rangesLeft.at(root->key) = {root->value + 1, rangesLeft.at(root->key).second};
                rangesRight.at(root->key) = {rangesRight.at(root->key).first, root->value};
                sum += solve_part_2(rangesLeft, nodes, initial, root->left);
                sum += solve_part_2(rangesRight, nodes, initial, root->right);
            }
        }
        else {
            if (root->key == "A") {
                ull value = 1;
                for (const auto& range : ranges) {
                    value = value * (range.second.second - range.second.first + 1);
                }
                return sum + value;
            }
            else if (root->key == "R") {
                return sum;
            }
            else {
                return sum + solve_part_2(ranges, nodes, initial, nodes[initial.at(root->key)]);
            }
        }
        return sum;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<tree*> nodes;

        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<std::string, int> initial;
        std::map<std::string, std::pair<unsigned long long, unsigned long long>> pairs {{"x", {1, 4000}}, {"m", {1, 4000}}, {"a", {1, 4000}}, {"s", {1, 4000}}};
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

        return solve_part_2(pairs, nodes, initial, nodes[initial["in"]]);
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
