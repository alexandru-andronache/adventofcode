#include "file.h"
#include <iostream>
#include <vector>

namespace aoc2017_day03 {
    int sum(const std::vector<std::vector<long long>>& map, int x, int y) {
        int s = 0;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                s += map[x + i][y + j];
            }
        }
        return s;
    }

    int part_1(int N = 347991) {
        int sol = 0;
        int k = 1;
        while (k * k < N) {
            k += 2;
            sol++;
        }
        k -= 2;
        int nr = k * k + 1;
        for (int i = 0; i < 4; ++i) {
            if (N <= nr + k) {
                return sol + abs(N - nr - k / 2);
            }
            nr += k + 1;
        }
        return -1;
    }

    int part_2(int N = 347991) {
        const int SIZE = 1000;
        std::vector<std::vector<long long>> map(SIZE, std::vector<long long>(SIZE, 0));

        int x = SIZE / 2, y = SIZE / 2;
        int k = 2;
        map[x][y] = 1;
        while (true) {
            y++;
            for (int i = 0; i < k; ++i) {
                map[x][y] = sum(map, x, y);
                if (map[x][y] > N) return map[x][y];
                x--;
            }
            x++;
            y--;
            for (int i = 0; i < k; ++i) {
                map[x][y] = sum(map, x, y);
                if (map[x][y] > N) return map[x][y];
                y--;
            }
            y++;
            x++;
            for (int i = 0; i < k; ++i) {
                map[x][y] = sum(map, x, y);
                if (map[x][y] > N) return map[x][y];
                x++;
            }
            x--;
            y++;
            for (int i = 0; i < k; ++i) {
                map[x][y] = sum(map, x, y);
                if (map[x][y] > N) return map[x][y];
                y++;
            }
            y--;
            k += 2;
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day03::part_1() << std::endl;
    std::cout << "Part 2: " << aoc2017_day03::part_2() << std::endl;

    return 0;
}
#endif
