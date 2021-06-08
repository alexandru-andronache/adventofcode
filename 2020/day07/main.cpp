#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <stack>
#include <set>

namespace aoc2020_day07 {
    int getIndex(std::map<std::string, int> &colors, int &id, const std::string &color) {
        if (colors.find(color) == colors.end()) {
            colors[color] = id;
            id++;
        }
        return colors[color];
    }

    void bfs(const std::vector<std::vector<int>> &connections, int root, int &sol, int multiplier) {
        for (int i = 0; i < connections[root].size(); ++i) {
            if (connections[root][i] > 0) {
                sol += connections[root][i] * multiplier;
                bfs(connections, i, sol, multiplier * connections[root][i]);
            }
        }
    }

    void parseInput(const std::vector<std::string> &input,
                    std::vector<std::vector<int>> &connections,
                    std::map<std::string, int> &colors) {
        int id = 0;
        for (const auto &line : input) {
            std::vector<std::string> words = utils::splitString(line, " .,");
            int indexMainColor = getIndex(colors, id, words[0] + " " + words[1]);
            int i = 3;
            while (i + 4 < words.size()) {
                int index = getIndex(colors, id, words[i + 2] + " " + words[i + 3]);
                connections[indexMainColor][index] = atoi(words[i + 1].c_str());
                i = i + 4;
            }
        }
    }

    int part_1(std::string_view path, const std::string &bag = "shiny gold", int n_max = 1000) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<std::string, int> colors;
        std::vector<std::vector<int>> connections(n_max, std::vector<int>(n_max, 0));
        parseInput(input, connections, colors);

        std::stack<int> indexes;
        indexes.push(colors[bag]);
        std::set<int> sol;
        while (!indexes.empty()) {
            int k = indexes.top();
            indexes.pop();
            for (int i = 0; i < connections[k].size(); ++i) {
                if (connections[i][k] > 0 && sol.find(i) == sol.end()) {
                    sol.insert(i);
                    indexes.push(i);
                }
            }
        }

        return sol.size();
    }

    int part_2(std::string_view path, const std::string &bag = "shiny gold", int n_max = 1000) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::map<std::string, int> colors;
        std::vector<std::vector<int>> connections(n_max, std::vector<int>(n_max, 0));
        parseInput(input, connections, colors);

        int sol = 0;
        bfs(connections, colors[bag], sol, 1);

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2020_day07::part_1("../2020/day07/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2020_day07::part_2("../2020/day07/input.in") << std::endl;

    return 0;
}
#endif
