#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <stack>
#include <set>

namespace aoc2017_day07 {
    struct tree{
        std::string name;
        int index;
        int sum;
        int weight;
        std::vector<tree*> childrens;
    };

    int newWeight = -1;

    void parseInput(const std::vector<std::tuple<std::string, int, std::vector<std::string>>>& input,
                    std::map<std::string, std::pair<int, int>>& names,
                    std::vector<std::vector<int>>& connection) {
        int index = 0;
        for (const auto& line :  input) {
            auto [name, weight, children] = line;
            int indexName = -1;
            if (names.find(name) != names.end()) {
                indexName = names[name].first;
                names[name].second = weight;
            }
            else {
                names[name].first = index;
                names[name].second = weight;
                indexName = index;
                index++;
            }

            for (const auto& c : children) {
                int indexChild = -1;
                if (names.find(c) != names.end()) {
                    indexChild = names[c].first;
                }
                else {
                    names[c].first = index;
                    names[c].second = 0;
                    indexChild = index;
                    index++;
                }
                connection[indexName][indexChild] = 1;
            }
        }
    }

    int findRoot(const std::map<std::string, std::pair<int, int>>& names,
                 const std::vector<std::vector<int>>& connection) {
        for (int j = 0; j < names.size(); ++j) {
            bool found = false;
            for (int i = 0; i < names.size(); ++i) {
                if (connection[i][j] == 1) found = true;
            }
            if (!found) {
                return j;
            }
        }
        return -1;
    }

    std::string findName(const std::map<std::string, std::pair<int, int>>& names, int index) {
        for (const auto& s : names) {
            if (s.second.first == index) return s.first;
        }
        return "";
    }

    int findWeight(const std::map<std::string, std::pair<int, int>>& names, int index) {
        for (const auto& s : names) {
            if (s.second.first == index) return s.second.second;
        }
        return 0;
    }

    void createTree(tree* root, const std::vector<std::vector<int>>& connections, const std::map<std::string, std::pair<int, int>>& names, int index, int nrMax) {
        root->name = findName(names, index);
        root->weight = findWeight(names, index);
        root->index = index;
        for (int i = 0; i < nrMax; ++i) {
            if (connections[index][i] == 1) {
                tree* tmp = new tree();
                tmp->name = findName(names, i);
                tmp->weight = findWeight(names, i);
                tmp->index = i;
                root->childrens.push_back(tmp);
            }
        }
        for (int i = 0; i < root->childrens.size(); ++i) {
            createTree(root->childrens[i], connections, names, root->childrens[i]->index, nrMax);
        }
    }

    void balanceTower(tree *root) {
        if (root->childrens.size() > 0) {
            for (int i = 0; i < root->childrens.size(); ++i) {
                balanceTower(root->childrens[i]);
            }
            std::vector<std::pair<int, int>> weight;
            for (int i = 0; i < root->childrens.size(); ++i) {
                weight.push_back({root->childrens[i]->sum, root->childrens[i]->weight});
            }
            std::sort(weight.begin(), weight.end(), [](auto a, auto b) {
                return a.first < b.first;
            });
            if (weight.size() > 1) {
                int n = weight.size() - 1;
                if (weight[0].first != weight[1].first) {
                    newWeight = weight[0].second + (weight[1].first - weight[0].first);
                }
                if (weight[n].first != weight[n - 1].first) {
                    newWeight = weight[n].second - (weight[n].first - weight[n - 1].first);
                }
                for (int i = 0; i < root->childrens.size(); ++i) {
                    root->childrens[i]->sum = weight[1].first;
                }
            }

            root->sum = weight[0].first * root->childrens.size() + root->weight;
        }
        else {
            root->sum = root->weight;
        };
    }

    std::string part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        std::vector<std::tuple<std::string, int, std::vector<std::string>>> input;
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " (),->\r");
            std::vector<std::string> names;
            for (int i = 2; i < tokens.size(); ++i) {
                names.push_back(tokens[i]);
            }
            input.push_back({tokens[0], std::stoi(tokens[1]), names});
        }

        const int SIZE = 2000;
        std::map<std::string, std::pair<int, int>> names;
        std::vector<std::vector<int>> connection(SIZE, std::vector<int>(SIZE, 0));
        parseInput(input, names, connection);

        return findName(names, findRoot(names, connection));
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        std::vector<std::tuple<std::string, int, std::vector<std::string>>> input;
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, " (),->\r");
            std::vector<std::string> names;
            for (int i = 2; i < tokens.size(); ++i) {
                names.push_back(tokens[i]);
            }
            input.push_back({tokens[0], std::stoi(tokens[1]), names});
        }

        const int SIZE = 2000;
        std::map<std::string, std::pair<int, int>> names;
        std::vector<std::vector<int>> connection(SIZE, std::vector<int>(SIZE, 0));
        parseInput(input, names, connection);

        tree* root = new tree();
        createTree(root, connection, names, findRoot(names, connection), names.size());

        balanceTower(root);

        return newWeight;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day07::part_1("../2017/day07/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day07::part_2("../2017/day07/input.in") << std::endl;

    return 0;
}
#endif
