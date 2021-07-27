#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>

namespace aoc2017_day12 {
    int part_1(std::string_view path, int id = 0) {
        std::vector<std::pair<int, std::vector<int>>> input;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<int> tokens = utils::splitStringToInt(line, "  <->,");
            input.push_back({tokens[0], {tokens.begin() + 1, tokens.end()}});
        }

        const int SIZE = 3000;
        std::vector<std::vector<bool>> pipes(SIZE, std::vector<bool>(SIZE, false));
        for (const auto& line : input) {
            for (const auto& x : line.second) {
                pipes[line.first][x] = pipes[x][line.first] = true;
            }
        }

        std::vector<bool> visited(SIZE, false);
        std::vector<int> sol;
        sol.push_back(0);
        visited[0] = true;
        int i = 0;
        while (i < sol.size()) {
            for (int j = 0; j < SIZE; ++j) {
                if (pipes[sol[i]][j] && !visited[j]) {
                    sol.push_back(j);
                    visited[j] = true;
                }
            }
            i++;
        }
        return sol.size();
    }

    int part_2(std::string_view path) {
        std::vector<std::pair<int, std::vector<int>>> input;
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& line : lines) {
            std::vector<int> tokens = utils::splitStringToInt(line, "  <->,");
            input.push_back({tokens[0], {tokens.begin() + 1, tokens.end()}});
        }

        const int SIZE = 3000;
        int max = 0;
        std::vector<std::vector<bool>> pipes(SIZE, std::vector<bool>(SIZE, false));
        for (const auto& line : input) {
            for (const auto& x : line.second) {
                pipes[line.first][x] = pipes[x][line.first] = true;
            }
            max = std::max(max, line.first);
        }

        std::vector<bool> visited(SIZE, false);
        int groups = 0;
        for (int k = 0; k <= max; ++k) {
            if (!visited[k]) {
                groups++;
                std::vector<int> sol;
                sol.push_back(k);
                visited[k] = true;
                int i = 0;
                while (i < sol.size()) {
                    for (int j = 0; j < SIZE; ++j) {
                        if (pipes[sol[i]][j] && !visited[j]) {
                            sol.push_back(j);
                            visited[j] = true;
                        }
                    }
                    i++;
                }
            }
        }
        return groups;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day12::part_1("../2017/day12/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day12::part_2("../2017/day12/input.in") << std::endl;

    return 0;
}
#endif
