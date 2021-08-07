#include "file.h"
#include "utilities.h"
#include <iostream>
#include <set>
#include <deque>

namespace aoc2018_day12 {
    int calculateSum(const std::deque<std::pair<int, bool>>& plants) {
        int sum = 0;
        for (const auto& p : plants) {
            if (p.second) {
                sum += p.first;
            }
        }
        return sum;
    }

    long long solve(const std::vector<bool>& input,
                    const std::vector<bool>& instructionsPlants,
                    unsigned long long generations = 20) {
        std::deque<std::pair<int, bool>> plants;
        std::deque<std::pair<int, bool>> prevPlants;
        for (int i = 0; i < input.size(); ++i) {
            plants.push_back(std::make_pair(i, input[i]));
        }

        for (unsigned long long g = 0; g < generations; ++g) {
            std::deque<std::pair<int, bool>> tmp;
            int N = 4, i = 0;
            auto it = plants.begin();
            while (i < N && !it->second) {
                i++;
                it++;
            }
            for (int k = 0; k < N - i; ++k) {
                plants.push_front(std::make_pair(plants.front().first - 1, false));
            }
            auto rit = plants.rbegin();
            i = 0;
            while (i < N && !rit->second) {
                i++;
                rit++;
            }
            for (int k = 0; k < N - i; ++k) {
                plants.emplace_back(plants.back().first + 1, false);
            }

            for (auto it = plants.begin() + 2; it != plants.end() - 2; ++it) {
                int x = (2 << 4) - 1;
                for (int i = -2; i <= 2; ++i) {
                    if (!(it + i)->second) x &= ~(1Ul << (2 - i));
                }
                tmp.emplace_back(it->first, instructionsPlants[x]);
            }
            if (prevPlants.size()  == tmp.size()) {
                bool similar = true;
                unsigned long long diff = 0;
                for (int j = 0; j < prevPlants.size(); ++j) {
                    if (prevPlants[j].second != tmp[j].second) {
                        similar = false;
                    }
                    if (prevPlants[j].second) {
                        diff += std::abs(prevPlants[j].first - tmp[j].first);
                    }
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
            int x = (2 << 4) - 1;
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
            int x = (2 << 4) - 1;
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
