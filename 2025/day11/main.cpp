#include "file.h"
#include "utilities.h"
#include <types.h>
#include <vector>

#include <fmt/printf.h>
#include <map>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2025_day11 {
    int findOrAddToMap(std::map<std::string, int>& data, const std::string& key, int& index) {
        if (!data.contains(key)) {
            data.insert({key, index});
            index++;
        }
        return data[key];
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int result = 0;
        std::map<std::string, int> data;
        int index = 0;
        std::vector<std::vector<bool>> grid(1000, std::vector<bool>(1000, false));

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ",: ");
            int start = findOrAddToMap(data, tokens[0], index);
            for (int i = 1; i < tokens.size(); i++) {
                int end = findOrAddToMap(data, tokens[i], index);
                grid[start][end] = true;
            }
        }

        int start = data["you"];
        std::vector<int> queue;
        queue.push_back(start);
        while (!queue.empty()) {
            int current = queue.front();
            queue.erase(queue.begin());
            if (current == data["out"]) {
                result++;
            }
            for (int i = 0; i < index; i++) {
                if (grid[current][i]) {
                    queue.push_back(i);
                }
            }
        }

        return result;
    }

    std::map<std::tuple<int, bool, bool>, ull> cache;
    std::map<std::string, int> data;

    ull dfs(std::map<int, std::vector<int>> &nodes, int curr, bool fft, bool dac) {
        if (curr == data["out"]) {
            return fft && dac;
        }
        ull ans = 0;

        if (cache.contains(std::tuple(curr, fft, dac))) {
            return cache[std::make_tuple(curr, fft, dac)];
        }

        for (const auto& child : nodes[curr]) {
            if (child == data["fft"])
                ans += dfs(nodes, child, true, dac);
            else if (child == data["dac"])
                ans += dfs(nodes, child, fft, true);
            else
                ans += dfs(nodes, child, fft, dac);
        }
        return cache[std::make_tuple(curr, fft, dac)] = ans;
    }

    ull part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        int index = 0;
        std::map<int, std::vector<int>> nodes;
        cache.clear();
        data.clear();

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ",: ");

            for (int i = 1; i < tokens.size(); i++) {
                nodes[findOrAddToMap(data, tokens[0], index)].push_back(findOrAddToMap(data, tokens[i], index));
            }
        }

        return dfs(nodes, data["svr"], false, false);
    }
}

#ifdef TESTING
    TEST(Test2025Day11, part_1_test) {
        ASSERT_EQ(aoc2025_day11::part_1("../2025/day11/input_test.in"), 5);
    }

    TEST(Test2025Day11, part_1_real_test) {
        ASSERT_EQ(aoc2025_day11::part_1("../2025/day11/input.in"), 428);
    }

    TEST(Test2025Day11, part_2_test) {
        ASSERT_EQ(aoc2025_day11::part_2("../2025/day11/input_test_part_2.in"), 2);
    }

    TEST(Test2025Day11, part_2_real_test) {
        ASSERT_EQ(aoc2025_day11::part_2("../2025/day11/input.in"), 331468292364745);
    }
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoc2025_day11::part_1("../2025/day11/input.in"));
    fmt::print("Part 2: {}\n", aoc2025_day11::part_1("../2025/day11/input.in"));

    return 0;
}
#endif
