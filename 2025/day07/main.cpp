#include "file.h"
#include "utilities.h"
#include <vector>

#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day07 {
    unsigned long long part_1(std::string_view path) {
        unsigned long long result = 0;

        std::vector<std::vector<char>> map = file::readFileAsMapChar(path);
        std::vector<std::vector<bool>> visited(map.size(), std::vector<bool>(map[0].size(), false));

        utils::point start = utils::findValue(map, 'S');
        std::set<utils::point> current_positions = {start};
        while (!current_positions.empty()) {
            std::set<utils::point> new_positions;
            std::vector<bool> visited_row(map[0].size(), false);
            for (const auto& pos : current_positions) {
                if (pos.x + 1 < map.size() && map[pos.x + 1][pos.y] == '.') {
                    new_positions.insert({pos.x + 1, pos.y});
                }
                else if (pos.x + 1 < map.size() && map[pos.x + 1][pos.y] == '^') {
                    bool add = false;
                    if (pos.y - 1 >= 0 && !visited_row[pos.y - 1]) {
                        new_positions.insert({pos.x + 1, pos.y - 1});
                        visited_row[pos.y - 1] = true;
                        add = true;
                    }
                    if (pos.y + 1 < map[0].size() && !visited_row[pos.y + 1]) {
                        new_positions.insert({pos.x + 1, pos.y + 1});
                        visited_row[pos.y + 1] = true;
                        add = true;
                    }
                    if (add) {
                        result++;
                    }
                }
            }
            current_positions = new_positions;
        }
        return result;
    }

    unsigned long long part_2(std::string_view path) {
        unsigned long long result = 0;

        std::vector<std::vector<char>> map = file::readFileAsMapChar(path);
        std::vector<std::vector<unsigned long long>> visited(map.size(), std::vector<unsigned long long>(map[0].size(), 0));

        utils::point start = utils::findValue(map, 'S');
        std::set<utils::point> current_positions = {start};
        visited[start.x][start.y] = 1;
        while (!current_positions.empty()) {
            std::set<utils::point> new_positions;
            for (const auto& pos : current_positions) {
                if (pos.x + 1 < map.size() && map[pos.x + 1][pos.y] == '.') {
                    new_positions.insert({pos.x + 1, pos.y});
                    visited[pos.x + 1][pos.y] += visited[pos.x][pos.y];
                }
                else if (pos.x + 1 < map.size() && map[pos.x + 1][pos.y] == '^') {
                    if (pos.y - 1 >= 0) {
                        new_positions.insert({pos.x + 1, pos.y - 1});
                        visited[pos.x + 1][pos.y - 1] += visited[pos.x][pos.y];
                    }
                    if (pos.y + 1 < map[0].size()) {
                        new_positions.insert({pos.x + 1, pos.y + 1});
                        visited[pos.x + 1][pos.y + 1] += visited[pos.x][pos.y];
                    }
                }
            }
            current_positions = new_positions;
        }
        for (int i = 0; i < map[0].size(); i++) {
            result += visited.back()[i];
        }
        return result;
    }
}

#ifdef TESTING
    TEST(Test2025Day07, part_1_test) {
        ASSERT_EQ(aoc2025_day07::part_1("../2025/day07/input_test.in"), 21);
    }

    TEST(Test2025Day07, part_1_real_test) {
        ASSERT_EQ(aoc2025_day07::part_1("../2025/day07/input.in"), 1524);
    }

    TEST(Test2025Day07, part_2_test) {
        ASSERT_EQ(aoc2025_day07::part_2("../2025/day07/input_test.in"), 40);
    }

    TEST(Test2025Day07, part_2_real_test) {
        ASSERT_EQ(aoc2025_day07::part_2("../2025/day07/input.in"), 32982105837605);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day07::part_1("../2025/day07/input_test.in"));
    fmt::print("Part 2: {}\n", aoc2025_day07::part_2("../2025/day07/input.in"));

    return 0;
}
#endif
