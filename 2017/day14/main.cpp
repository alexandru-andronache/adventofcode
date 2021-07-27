#include "file.h"
#include <iostream>
#include <numeric>
#include <map>
#include <sstream>
#include <iomanip>
#include <queue>

namespace aoc2017_day14 {
    int part_1(std::string input,  int size = 256, int rounds = 64) {
        int sol = 0;
        for (int k = 0; k < 128; ++k) {
            std::string newKey = input + "-" + std::to_string(k);
            int currentPosition = 0;
            int skip = 0;
            std::vector<int> list;
            for (int i = 0; i < size; ++i) {
                list.push_back(i);
            }
            std::vector<int> lengths;
            for (auto s : newKey) {
                lengths.push_back(s);
            }
            lengths.insert(lengths.end(), {17, 31, 73, 47, 23});

            for (int r = 0; r < rounds; ++r) {
                for (const auto &x : lengths) {
                    for (int i = 0; i < x / 2; ++i) {
                        std::swap(list[(currentPosition + i) % size], list[(currentPosition - i + x - 1) % size]);
                    }
                    currentPosition = (currentPosition + x + skip) % size;
                    skip++;
                }
            }

            std::vector<int> output(16, 0);
            for (int i = 0; i < 16; ++i) {
                output[i] = list[i * 16];
                for (int j = 1; j < 16; ++j) {
                    output[i] = output[i] ^ list[i * 16 + j];
                }
            }

            std::stringstream stream;
            for (int i = 0; i < 16; ++i) {
                stream << std::hex << output[i];
            }

            for (char l : stream.str()) {
                if (l >= 'a' && l <= 'f') {
                    sol += std::bitset<4>(l - 'a' + 10).count();
                }
                else {
                    sol += std::bitset<4>(l - '0').count();
                }
            }
        }

        return sol;
    }

    int part_2(std::string input, int size = 256, int rounds = 64) {
        int sol = 0;
        std::vector<std::vector<bool>> map(128, std::vector<bool>());
        std::vector<std::vector<bool>> visited(128, std::vector<bool>(128, false));
        for (int k = 0; k < 128; ++k) {
            std::string newKey = input + "-" + std::to_string(k);
            int currentPosition = 0;
            int skip = 0;
            std::vector<int> list;
            for (int i = 0; i < size; ++i) {
                list.push_back(i);
            }
            std::vector<int> lengths;
            for (auto s : newKey) {
                lengths.push_back(s);
            }
            lengths.insert(lengths.end(), {17, 31, 73, 47, 23});

            for (int r = 0; r < rounds; ++r) {
                for (const auto &x : lengths) {
                    for (int i = 0; i < x / 2; ++i) {
                        std::swap(list[(currentPosition + i) % size], list[(currentPosition - i + x - 1) % size]);
                    }
                    currentPosition = (currentPosition + x + skip) % size;
                    skip++;
                }
            }

            std::vector<int> output(16, 0);
            for (int i = 0; i < 16; ++i) {
                output[i] = list[i * 16];
                for (int j = 1; j < 16; ++j) {
                    output[i] = output[i] ^ list[i * 16 + j];
                }
            }

            std::stringstream stream;
            for (int i = 0; i < 16; ++i) {
                stream << std::hex << std::setw(2) << std::setfill('0') << output[i];
            }

            for (char l : stream.str()) {
                if (l >= 'a' && l <= 'f') {
                    for (const auto& x : std::bitset<4>(l - 'a' + 10).to_string()) {
                        if (x == '1') {
                            map[k].push_back(true);
                        }
                        else {
                            map[k].push_back(false);
                        }
                    }
                }
                else {
                    for (const auto& x : std::bitset<4>(l - '0').to_string()) {
                        if (x == '1') {
                            map[k].push_back(true);
                        }
                        else {
                            map[k].push_back(false);
                        }
                    }
                }
            }
        }

        for (int i = 0; i < map.size(); ++i) {
            for (int j = 0; j < map[i].size(); ++j) {
                if (map[i][j] && !visited[i][j]) {
                    sol++;
                    std::queue<std::pair<int, int>> points;
                    points.push({i, j});
                    while (!points.empty()) {
                        auto it = points.front();
                        points.pop();
                        std::vector<std::pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                        for (const auto& d : directions) {
                            if (it.first + d.first >= 0 && it.first + d.first < map.size() &&
                            it.second + d.second >= 0 && it.second + d.second < map[0].size() &&
                            map[it.first + d.first][it.second + d.second] &&
                            !visited[it.first + d.first][it.second + d.second]) {
                                points.push({it.first + d.first, it.second + d.second});
                                visited[it.first + d.first][it.second + d.second] = true;
                            }
                        }
                    }
                }
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day14::part_1("stpzcrnm") << std::endl;
    std::cout << "Part 1: " << aoc2017_day14::part_2("stpzcrnm") << std::endl;

    return 0;
}
#endif
