#include "file.h"
#include "utilities.h"
#include <fmt/printf.h>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoccodes_2024_day07 {
    std::string part_1(std::string_view path, int turns = 10) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::pair<int, std::string>> races;
        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ":,");
            int speed = 10;
            int sum = 0;
            races.emplace_back(sum, tokens[0]);
            tokens.erase(tokens.begin());
            for (int turn = 0, j = 0; turn < turns; ++turn) {
                if (tokens[j] == "+") {
                    speed++;
                }
                else if (tokens[j] == "-") {
                    speed--;
                }
                sum += speed;
                j = (j + 1) % tokens.size();
            }
            races.back().first += sum;
        }
        std::sort(races.begin(), races.end(), [](const auto& first, const auto& second) {
            return first.first > second.first;
        });
        std::string sol;
        for (const auto& race : races) {
            sol += race.second;
        }
        return sol;
    }

    void advance(char position, const std::string& tokens, int& speed, int& index, int& sum) {
        if (position == '+') {
            speed ++;
        }
        else if (position == '-') {
            speed = std::max(speed - 1, 0);
        }
        else {
            if (tokens[index] == '+') {
                speed++;
            }
            else if (tokens[index] == '-') {
                speed = std::max(speed - 1, 0);
            }
        }
        index = (index + 1) % tokens.size();
        sum += speed;
    }

    std::string part_2(std::string_view path, std::string_view pathTrack, int laps = 10) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::string> track = file::readFileAsArrayString(pathTrack);
        std::vector<std::pair<int, std::string>> races;

        std::string round;
        for (int i = 1; i < track[0].size(); ++i) {
            round += track[0][i];
        }
        for (int i = 1; i < track.size(); ++i) {
            round += track[i][track[i].size() - 1];
        }
        for (int i = track[0].size() - 2; i >= 0; --i) {
            round += track[track.size() - 1][i];
        }
        for (int i = track.size() - 2; i >= 0; --i) {
            round += track[i][0];
        }

        for (const auto& line : lines) {
            std::vector<std::string> tokens = utils::splitString(line, ":,");
            int j = 0;
            int speed = 10;
            int sum = 0;
            std::string token;
            races.emplace_back(sum, tokens[0]);
            for (int i = 1; i < tokens.size(); ++i) {
                token += tokens[i];
            }
            for (int lap = 0; lap < laps; ++lap) {
                for (const auto& r : round) {
                    advance(r, token, speed, j, sum);
                }
            }
            races.back().first += sum;
        }
        std::sort(races.begin(), races.end(), [](const auto& first, const auto& second) {
            return first.first > second.first;
        });
        std::string sol;
        for (const auto& race : races) {
            sol += race.second;
        }
        return sol;
    }

    bool validCharacter(char c) {
        return c == '+' || c == '-' || c == 'S' || c == '=';
    }

    std::string precompute(std::string_view path) {
        std::vector<std::string> track = file::readFileAsArrayString(path);
        std::vector<std::vector<bool>> visited(track.size(), std::vector<bool>(track[0].size(), false));
        std::string sol;

        int x = 0, y = 1;
        visited[x][y] = true;
        visited[0][0] = true;
        sol += track[x][y];

        do {
            std::vector<utils::point> dir = utils::getListOfNeighbours4Directions2(x, y, track.size(), track[0].size());
            for (const auto& d : dir) {
                if (!visited[d.x][d.y] && validCharacter(track[d.x][d.y])) {
                    visited[d.x][d.y] = true;
                    sol += track[d.x][d.y];
                    x = d.x;
                    y = d.y;
                    break;
                }
            }
            visited[0][0] = false;
        }
        while (track[x][y] != 'S');

        return sol;
    }

    unsigned long long calculate_part_3(std::string_view path, const std::string& tokens, int laps = 2024) {
        int sum = 0;
        int speed = 10;
        int index = 0;
        for (int lap = 0; lap < laps; ++lap) {
            for (char i : path) {
                advance(i, tokens, speed, index, sum);
            }
        }
        return sum;
    }

    int part_3(std::string_view path, std::string_view pathTrack) {
        std::string plan = file::readFileAsString(path);
        std::string t = precompute(pathTrack);
        int sol = 0;
        std::vector<std::string> tokens = utils::splitString(plan, ":,");
        tokens.erase(tokens.begin());
        std::string initial;
        for (const auto& token : tokens) {
            initial += token;
        }

        unsigned long long score = calculate_part_3(t, initial, 11);

        std::string test = "+++++---===";
        do
        {
            unsigned long long result = calculate_part_3(t, test, 11);
            if (result > score) {
                sol++;
            }
        }
        while (std::next_permutation(test.begin(), test.end()));

        return sol;
    }
}

#ifdef TESTING
namespace aoccodes_2024_day07 {
    TEST(Testscodes_2024Day07, part_1_test) {
        ASSERT_EQ(part_1("../codes_2024/day07/input/input_part_1_test.in"), "BDCA");
    }

    TEST(Testscodes_2024Day07, part_1_real_test) {
        ASSERT_EQ(part_1("../codes_2024/day07/input/input_part_1.in"), "GKDIHBEJC");
    }

    TEST(Testscodes_2024Day07, part_2_test) {
        ASSERT_EQ(part_2("../codes_2024/day07/input/input_part_2_test.in", "../codes_2024/day07/input/input_part_2_test_extra.in"), "DCBA");
    }

    TEST(Testscodes_2024Day07, part_2_real_test) {
        ASSERT_EQ(part_2("../codes_2024/day07/input/input_part_2.in", "../codes_2024/day07/input/input_part_2_extra.in"), "EIKDGJFAC");
    }

    TEST(Testscodes_2024Day07, part_3_real_test) {
        ASSERT_EQ(part_3("../codes_2024/day07/input/input_part_3.in", "../codes_2024/day07/input/input_part_3_extra.in"), 4060);
    }
}
#endif

#ifndef TESTING
int main() {
    fmt::print("Part 1: {}\n", aoccodes_2024_day07::part_1("../codes_2024/day07/input/input_part_1.in"));
    fmt::print("Part 2: {}\n", aoccodes_2024_day07::part_2("../codes_2024/day07/input/input_part_2.in", "../codes_2024/day07/input/input_part_2_extra.in"));
    fmt::print("Part 3: {}\n", aoccodes_2024_day07::part_3("../codes_2024/day07/input/input_part_3.in", "../codes_2024/day07/input/input_part_3_extra.in"));

    return 0;
}
#endif
