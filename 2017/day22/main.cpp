#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2017_day22 {
    int part_1(std::string_view path, int bursts = 10000) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        constexpr int N_MAX = 1000;
        std::vector<std::vector<bool>> map(N_MAX, std::vector<bool>(N_MAX, false));

        int x = N_MAX / 2, y = N_MAX / 2;
        for (const auto& line : input) {
            for (const auto& c : line) {
                if (c == '#') {
                    map[x][y] = true;
                }
                y++;
            }
            y = N_MAX / 2;
            x++;
        }

        x = N_MAX / 2 + input.size() / 2;
        y = N_MAX / 2 + input[0].size() / 2;
        int infections = 0;
        std::pair<int, int> dir(-1, 0);
        for (int burst = 0; burst < bursts; ++burst) {
            std::pair<int, int> newDir(dir.second, dir.first);
            if (map[x][y] && dir.first != 0) {
                newDir.second = -newDir.second;
            }
            else if (!map[x][y] && dir.second != 0) {
                newDir.first = -newDir.first;
            }
            if (!map[x][y]) {
                infections++;
            }
            map[x][y] = !map[x][y];
            x += newDir.first;
            y += newDir.second;
            dir = newDir;
        }

        return infections;
    }

    int part_2(std::string_view path, int bursts = 10000000) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        constexpr int N_MAX = 10000;
        std::vector<std::vector<int>> map(N_MAX, std::vector<int>(N_MAX, 0));
        // 0 - clean, 1 - Weakened, 2 - Infected, 3 - Flagged

        int x = N_MAX / 2, y = N_MAX / 2;
        for (const auto& line : input) {
            for (const auto& c : line) {
                if (c == '#') {
                    map[x][y] = 2;
                }
                y++;
            }
            y = N_MAX / 2;
            x++;
        }

        x = N_MAX / 2 + input.size() / 2;
        y = N_MAX / 2 + input[0].size() / 2;
        int infections = 0;
        std::pair<int, int> dir(-1, 0);
        for (int burst = 0; burst < bursts; ++burst) {
            std::pair<int, int> newDir;
            if (map[x][y] == 1) {
                newDir = dir;
            }
            else if (map[x][y] == 3) {
                newDir.first = -dir.first;
                newDir.second = -dir.second;
            }
            else if (map[x][y] == 0) {
                if (dir.second != 0) {
                    newDir.first = -dir.second;
                    newDir.second = -dir.first;
                }
                else {
                    newDir.first = dir.second;
                    newDir.second = dir.first;
                }
            }
            else if (map[x][y] == 2) {
                if (dir.first != 0) {
                    newDir.first = -dir.second;
                    newDir.second = -dir.first;
                }
                else {
                    newDir.first = dir.second;
                    newDir.second = dir.first;
                }
            }

            map[x][y] = (map[x][y] + 1) % 4;
            if (map[x][y] == 2) {
                infections++;
            }
            x += newDir.first;
            y += newDir.second;
            dir = newDir;
        }

        return infections;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day22::part_1("../2017/day22/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day22::part_2("../2017/day22/input.in") << std::endl;

    return 0;
}
#endif
