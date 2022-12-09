#include "file.h"
#include "utilities.h"
#include <iostream>
#include <numeric>
#include <map>

namespace aoc2022_day09 {
    int sgn(int val) {
        return (val > 0) - (val < 0);
    }
    void updateTail(std::vector<utils::point>& tail) {
        for (auto it = std::next(tail.begin()); it != tail.end(); ++it) {
            if (std::abs(it->x - std::prev(it)->x) > 1 || std::abs(it->y - std::prev(it)->y) > 1) {
                it->y += sgn(std::prev(it)->y - it->y);
                it->x += sgn(std::prev(it)->x - it->x);
            }
        }
    }

    int solve(std::string_view path, int size) {
        const int N = 2000;
        std::vector<std::vector<bool>> prev(N, std::vector<bool>(N, false));
        std::map<std::string, utils::point> dir {{"R", {0, 1}},
                                                 {"L", {0, -1}},
                                                 {"U", {-1, 0}},
                                                 {"D", {1, 0}}};

        std::vector<std::string> input = file::readFileAsArrayString(path);
        std::vector<utils::point> tail {};
        prev[N / 2][N / 2] = true;
        for (int i = 0; i < size; ++i) {
            tail.push_back({N / 2, N / 2});
        }
        for (const auto& line : input) {
            std::vector<std::string> t = utils::splitString(line, " ");
            int steps = std::stoi(t[1]);

            for (int i = 0; i < steps; ++i) {
                tail[0].x += dir[t[0]].x;
                tail[0].y += dir[t[0]].y;
                updateTail(tail);
                prev[tail.back().x][tail.back().y] = true;
            }
        }

        return std::accumulate(prev.cbegin(), prev.cend(), 0, [](auto lhs, const auto& rhs) {
            return std::accumulate(rhs.cbegin(), rhs.cend(), lhs);
        });
    }

    int part_1(std::string_view path) {
        return solve(path, 2);
    }

    int part_2(std::string_view path) {
        return solve(path, 10);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day09::part_1("../2022/day09/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day09::part_2("../2022/day09/input.in") << std::endl;

    return 0;
}
#endif
