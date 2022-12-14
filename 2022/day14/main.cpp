#include "file.h"
#include "utilities.h"
#include <iostream>
#include <numeric>
#include <map>

namespace aoc2022_day14 {
    const int N = 1000;

    enum class terrain {
        Nothing = 0,
        Wall = 1,
        Sand = 2
    };

    void flow(int startX, int startY, std::vector<std::vector<terrain>> &map, int maxX) {
        bool overflow = false;
        while (!overflow && map[startX][startY] != terrain::Sand) {
            overflow = true;

            int x = startX;
            int y = startY;
            bool fall = true;
            while (x <= maxX && fall) {
                fall = false;
                while (x <= maxX && map[x + 1][y] == terrain::Nothing) {
                    x++;
                    fall = true;
                }
                if (map[x + 1][y - 1] == terrain::Nothing) {
                    x = x + 1;
                    y = y - 1;
                    fall = true;
                }
                else if (map[x + 1][y + 1] == terrain::Nothing) {
                    x = x + 1;
                    y = y + 1;
                    fall = true;
                }
            }

            if (x < maxX) {
                map[x][y] = terrain::Sand;
                overflow = false;
            }
        }
    }

    int readData(std::string_view path, std::vector<std::vector<terrain>>& map) {
        std::vector<std::string> input = file::readFileAsArrayString(path);
        int maxX = 0;

        for (const auto& l : input) {
            std::vector<int> t = utils::splitStringToInt(l, "-> ,");
            for (int i = 0; i < t.size() - 2; i += 2) {
                maxX = std::max(maxX, t[i + 1]);
                if (t[i] == t[i + 2]) {
                    for (int j = std::min(t[i + 1], t[i + 3]); j <= std::max(t[i + 1], t[i + 3]); ++j) {
                        map[j][t[i]] = terrain::Wall;
                    }
                }
                else {
                    for (int j = std::min(t[i], t[i + 2]); j <= std::max(t[i], t[i + 2]); ++j) {
                        map[t[i + 1]][j] = terrain::Wall;
                    }
                }
            }
        }

        return maxX;
    }

    int part_1(std::string_view path) {
        std::vector<std::vector<terrain>> map(N, std::vector<terrain>(N, terrain::Nothing));
        int maxX = readData(path, map);

        flow(0, 500, map, maxX);

        int sand = 0;
        for (const auto& l : map) {
            sand += std::count(l.begin(), l.end(), terrain::Sand);
        }

        return sand;
    }

    int part_2(std::string_view path) {
        std::vector<std::vector<terrain>> map(N, std::vector<terrain>(N, terrain::Nothing));
        int maxX = readData(path, map);

        for (int i = 0; i < N; ++i) {
            map[maxX + 2][i] = terrain::Wall;
        }

        flow(0, 500, map, maxX + 2);

        int sand = 0;
        for (const auto& l : map) {
            sand += std::count(l.begin(), l.end(), terrain::Sand);
        }

        return sand;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day14::part_1("../2022/day14/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2022_day14::part_2("../2022/day14/input.in") << std::endl;

    return 0;
}
#endif
