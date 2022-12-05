#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <string>
#include <stack>

namespace aoc2022_day05 {
    std::string part_1(std::string_view path) {
        std::string sol = "";
        int size = 0;
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::stack<char>> q;
        {
            int i = 0;
            while (input[i][1] != '1') {
                size++;
                i++;
            }
        }
        std::vector<int> index = utils::splitStringToInt(input[size], " ");
        for (int i = 0; i < index.size(); ++i) {
            q.push_back({});
        }

        for (int i = size - 1; i >= 0; --i) {
            for (int j = 0, pos = 0; j < input[i].size(); j += 4, pos++) {
                if (input[i][j + 1] != ' ') {
                    q[pos].push(input[i][j + 1]);
                }
            }
        }

        for (int i = size + 2; i < input.size(); ++i) {
            std::vector<std::string> t = utils::splitString(input[i], " ");
            int nr = std::stoi(t[1]);
            int from = std::stoi(t[3]) - 1;
            int to = std::stoi(t[5]) - 1;
            for (int j = 0; j < nr; ++j) {
                q[to].push(q[from].top());
                q[from].pop();
            }
        }

        for (int i = 0; i < q.size(); ++i) {
            sol += q[i].top();
        }
        return sol;
    }

    std::string part_2(std::string_view path) {
        std::string sol = "";
        int size = 0;
        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<std::stack<char>> q;
        {
            int i = 0;
            while (input[i][1] != '1') {
                size++;
                i++;
            }
        }
        std::vector<int> index = utils::splitStringToInt(input[size], " ");
        for (int i = 0; i < index.size(); ++i) {
            q.push_back({});
        }

        for (int i = size - 1; i >= 0; --i) {
            for (int j = 0, pos = 0; j < input[i].size(); j += 4, pos++) {
                if (input[i][j + 1] != ' ') {
                    q[pos].push(input[i][j + 1]);
                }
            }
        }

        for (int i = size + 2; i < input.size(); ++i) {
            std::vector<std::string> t = utils::splitString(input[i], " ");
            int nr = std::stoi(t[1]);
            int from = std::stoi(t[3]) - 1;
            int to = std::stoi(t[5]) - 1;
            std::vector<char> tmp;
            for (int j = 0; j < nr; ++j) {
                tmp.push_back(q[from].top());
                q[from].pop();
            }
            for (int j = tmp.size() - 1; j >= 0; --j) {
                q[to].push(tmp[j]);
            }
        }

        for (int i = 0; i < q.size(); ++i) {
            sol += q[i].top();
        }
        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day05::part_1("../2022/day05/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day05::part_2("../2022/day05/input.in") << std::endl;

    return 0;
}
#endif
