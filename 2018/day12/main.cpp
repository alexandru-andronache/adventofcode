#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>
#include <deque>
#include <numeric>

namespace aoc2018_day12 {
    int calculateSum(const std::deque<std::pair<int, bool>>& plants) {
        return std::accumulate(plants.begin(), plants.end(), 0, [](int s, const auto& plant) {
            return s + plant.first * plant.second;
        });
    }

    unsigned long long solve(const std::vector<bool>& input,
                    const std::vector<bool>& instructionsPlants,
                    unsigned long long generations = 20) {
        std::deque<std::pair<int, bool>> plants;
        std::deque<std::pair<int, bool>> prevPlants;
        for (int i = 0; i < input.size(); ++i) {
            plants.emplace_back(i, input[i]);
        }

        for (unsigned long long g = 0; g < generations; ++g) {
            std::deque<std::pair<int, bool>> tmp;
            int N = 4, i = 0;
            while (i < N && !(plants.begin() + i)->second) {
                i++;
            }
            for (int k = 0; k < N - i; ++k) {
                plants.push_front(std::make_pair(plants.front().first - 1, false));
            }
            i = 0;
            while (i < N && !(plants.rbegin() + i)->second) {
                i++;
            }
            for (int k = 0; k < N - i; ++k) {
                plants.emplace_back(plants.back().first + 1, false);
            }

            for (auto it = plants.begin() + 2; it != plants.end() - 2; ++it) {
                unsigned int x = (2 << 4) - 1;
                for (int k = -2; k <= 2; ++k) {
                    if (!(it + k)->second) x &= ~(1Ul << (2 - k));
                }
                tmp.emplace_back(it->first, instructionsPlants[x]);
            }
            if (prevPlants.size()  == tmp.size()) {
                bool similar = true;
                unsigned long long diff = 0;
                for (int j = 0; j < prevPlants.size(); ++j) {
                    similar = similar && (prevPlants[j].second == tmp[j].second);
                    diff += std::abs(prevPlants[j].first - tmp[j].first) * prevPlants[j].second;
                }
                if (similar) {
                    return (generations - g - 1) * diff + calculateSum(tmp);
                }
            }
            plants = tmp;
            prevPlants = tmp;
        }

        return calculateSum(plants);
    }

    long long part_1(std::string_view path) {
        std::vector<bool> plants;
        std::vector<bool> instructionsPlants(32, false);
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& l : lines[0]) {
            if (l == '#') {
                plants.push_back(true);
            }
            else if (l == '.') {
                plants.push_back(false);
            }
        }

        for (int k = 2; k < lines.size(); ++k) {
            unsigned int x = (2 << 4) - 1;
            for (int i = 0; i < 5; ++i) {
                if (lines[k][i] == '.') {
                    x &= ~(1UL << (4 - i));
                }
            }
            if (lines[k][9] == '#') {
                instructionsPlants[x] = true;
            }
        }

        return solve(plants, instructionsPlants);
    }

    long long part_2(std::string_view path) {
        std::vector<bool> plants;
        std::vector<bool> instructionsPlants(32, false);
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        for (const auto& l : lines[0]) {
            if (l == '#') {
                plants.push_back(true);
            }
            else if (l == '.') {
                plants.push_back(false);
            }
        }

        for (int k = 2; k < lines.size(); ++k) {
            unsigned int x = (2 << 4) - 1;
            for (int i = 0; i < 5; ++i) {
                if (lines[k][i] == '.') {
                    x &= ~(1UL << (4 - i));
                }
            }
            if (lines[k][9] == '#') {
                instructionsPlants[x] = true;
            }
        }

        return solve(plants, instructionsPlants, 50000000000);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day12::part_1("../2018/day12/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day12::part_2("../2018/day12/input.in") << std::endl;

    return 0;
}
#endif
