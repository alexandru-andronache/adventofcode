#include "file.h"
#include "utilities.h"
#include "direction.h"
#include <iostream>
#include <cmath>
#include <optional>
#include <map>

namespace aoc2019_day20 {
    struct tile {
        bool wall {true};
        std::string gate;
        int steps {std::numeric_limits<int>::max()};
    };

    struct gate {
        utils::point p1{-1, -1};
        utils::point p2{-1, -1};
    };

    struct point {
        point(int i, int j, int z)
        : x(i), y(j), depth(z) {
        }
        int x {0};
        int y {0};
        int depth {0};
    };
    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        size_t max = 0;
        for (const auto& line : lines) {
            max = std::max(max, line.size());
        }
        std::vector<std::vector<tile>> board(lines.size(), std::vector<tile>(max, {true, "", std::numeric_limits<int>::max()}));
        std::map<std::string, gate> gates;

        for (int i = 0; i < lines.size(); ++i) {
            for (int j = 0; j < max; ++j) {
                if (lines[i][j] == '.') {
                    board[i][j].wall = false;
                }
                else if (lines[i][j] >= 'A' && lines[i][j] <= 'Z') {
                    if (lines[i + 1][j] >= 'A' && lines[i + 1][j] <= 'Z') {
                        if (i + 2 < lines.size() && lines[i + 2][j] == '.') {
                            board[i + 2][j].gate = board[i][j].gate + lines[i][j] + lines[i + 1][j];
                            board[i + 2][j].wall = false;
                        }
                        else {
                            board[i - 1][j].gate = board[i + 1][j].gate + lines[i][j] + lines[i + 1][j];
                            board[i - 1][j].wall = false;
                        }
                    }
                    else if (lines[i][j + 1] >= 'A' && lines[i][j + 1] <= 'Z') {
                        if (j + 2 < max && lines[i][j + 2] == '.') {
                            board[i][j + 2].gate = board[i][j].gate + lines[i][j] + lines[i][j + 1];
                            board[i][j + 2].wall = false;
                        }
                        else {
                            board[i][j - 1].gate = board[i][j + 1].gate + lines[i][j] + lines[i][j + 1];
                            board[i][j - 1].wall = false;
                        }
                    }
                }
            }
        }

        std::vector<point> positions;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j].gate == "AA") {
                    positions.emplace_back(i, j, 0);
                    board[i][j].steps = 0;
                }
                if (!board[i][j].gate.empty()) {
                    if (gates.find(board[i][j].gate) != gates.end()) {
                        gates[board[i][j].gate].p2 = {i , j};
                    }
                    else {
                        gates.insert({board[i][j].gate, {{i, j}, {}}});
                    }
                }
            }
        }

        while (!positions.empty()) {
            std::vector<point> newPositions;
            for (const auto& pos : positions) {
                for (const auto& direction : direction::directions) {
                    if (pos.x + direction.first >= 0 && pos.x + direction.first < board.size() &&
                        pos.y + direction.second >= 0 && pos.y + direction.second < board[0].size() &&
                        !board[pos.x + direction.first][pos.y + direction.second].wall &&
                        board[pos.x + direction.first][pos.y + direction.second].steps > board[pos.x][pos.y].steps + 1) {
                        if (board[pos.x + direction.first][pos.y + direction.second].gate.empty()) {
                            board[pos.x + direction.first][pos.y + direction.second].steps = board[pos.x][pos.y].steps + 1;
                            newPositions.emplace_back(pos.x + direction.first, pos.y + direction.second, 0);
                        }
                        else {
                            board[pos.x + direction.first][pos.y + direction.second].steps = board[pos.x][pos.y].steps + 1;
                            if (board[pos.x + direction.first][pos.y + direction.second].gate != "ZZ") {
                                auto gatePositions = gates[board[pos.x + direction.first][pos.y + direction.second].gate];
                                if (pos.x + direction.first == gatePositions.p1.x &&
                                    pos.y + direction.second == gatePositions.p1.y) {
                                    if (board[gatePositions.p2.x][gatePositions.p2.y].steps > board[gatePositions.p1.x][gatePositions.p1.y].steps + 1) {
                                        board[gatePositions.p2.x][gatePositions.p2.y].steps = board[gatePositions.p1.x][gatePositions.p1.y].steps + 1;
                                        newPositions.emplace_back(gatePositions.p2.x, gatePositions.p2.y, 0);
                                    }
                                }
                                else {
                                    if (board[gatePositions.p1.x][gatePositions.p1.y].steps > board[gatePositions.p2.x][gatePositions.p2.y].steps + 1) {
                                        board[gatePositions.p1.x][gatePositions.p1.y].steps = board[gatePositions.p2.x][gatePositions.p2.y].steps + 1;
                                        newPositions.emplace_back(gatePositions.p1.x, gatePositions.p1.y, 0);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            positions = newPositions;
        }

        return board[gates["ZZ"].p1.x][gates["ZZ"].p1.y].steps;
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        size_t max = 0;
        for (const auto& line : lines) {
            max = std::max(max, line.size());
        }
        std::vector<std::vector<tile>> board(lines.size(), std::vector<tile>(max, {true, "", std::numeric_limits<int>::max()}));
        std::map<std::string, gate> gates;

        for (int i = 0; i < lines.size(); ++i) {
            for (int j = 0; j < max; ++j) {
                if (lines[i][j] == '.') {
                    board[i][j].wall = false;
                }
                else if (lines[i][j] >= 'A' && lines[i][j] <= 'Z') {
                    if (lines[i + 1][j] >= 'A' && lines[i + 1][j] <= 'Z') {
                        if (i + 2 < lines.size() && lines[i + 2][j] == '.') {
                            board[i + 2][j].gate = board[i][j].gate + lines[i][j] + lines[i + 1][j];
                            board[i + 2][j].wall = false;
                        }
                        else {
                            board[i - 1][j].gate = board[i + 1][j].gate + lines[i][j] + lines[i + 1][j];
                            board[i - 1][j].wall = false;
                        }
                    }
                    else if (lines[i][j + 1] >= 'A' && lines[i][j + 1] <= 'Z') {
                        if (j + 2 < max && lines[i][j + 2] == '.') {
                            board[i][j + 2].gate = board[i][j].gate + lines[i][j] + lines[i][j + 1];
                            board[i][j + 2].wall = false;
                        }
                        else {
                            board[i][j - 1].gate = board[i][j + 1].gate + lines[i][j] + lines[i][j + 1];
                            board[i][j - 1].wall = false;
                        }
                    }
                }
            }
        }

        std::vector<point> positions;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j].gate == "AA") {
                    positions.emplace_back(i, j, 0);
                    board[i][j].steps = 0;
                }
                if (!board[i][j].gate.empty()) {
                    if (gates.find(board[i][j].gate) != gates.end()) {
                        gates[board[i][j].gate].p2 = {i , j};
                    }
                    else {
                        gates.insert({board[i][j].gate, {{i, j}, {}}});
                    }
                }
            }
        }

        while (!positions.empty()) {
            std::vector<point> newPositions;
            for (const auto& pos : positions) {
                for (const auto& direction : direction::directions) {
                    if (pos.x + direction.first >= 0 && pos.x + direction.first < board.size() &&
                    pos.y + direction.second >= 0 && pos.y + direction.second < board[0].size() &&
                    !board[pos.x + direction.first][pos.y + direction.second].wall &&
                    board[pos.x + direction.first][pos.y + direction.second].steps > board[pos.x][pos.y].steps + 1) {
                        if (board[pos.x + direction.first][pos.y + direction.second].gate.empty()) {
                            board[pos.x + direction.first][pos.y + direction.second].steps = board[pos.x][pos.y].steps + 1;
                            newPositions.emplace_back(pos.x + direction.first, pos.y + direction.second, 0);
                        }
                        else {
                            board[pos.x + direction.first][pos.y + direction.second].steps = board[pos.x][pos.y].steps + 1;
                            if (board[pos.x + direction.first][pos.y + direction.second].gate != "ZZ") {
                                auto gatePositions = gates[board[pos.x + direction.first][pos.y + direction.second].gate];
                                if (pos.x + direction.first == gatePositions.p1.x &&
                                pos.y + direction.second == gatePositions.p1.y) {
                                    if (board[gatePositions.p2.x][gatePositions.p2.y].steps > board[gatePositions.p1.x][gatePositions.p1.y].steps + 1) {
                                        board[gatePositions.p2.x][gatePositions.p2.y].steps = board[gatePositions.p1.x][gatePositions.p1.y].steps + 1;
                                        newPositions.emplace_back(gatePositions.p2.x, gatePositions.p2.y, 0);
                                    }
                                }
                                else {
                                    if (board[gatePositions.p1.x][gatePositions.p1.y].steps > board[gatePositions.p2.x][gatePositions.p2.y].steps + 1) {
                                        board[gatePositions.p1.x][gatePositions.p1.y].steps = board[gatePositions.p2.x][gatePositions.p2.y].steps + 1;
                                        newPositions.emplace_back(gatePositions.p1.x, gatePositions.p1.y, 0);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            positions = newPositions;
        }

        return board[gates["ZZ"].p1.x][gates["ZZ"].p1.y].steps;
    }

}


#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day20::part_1("../2019/day20/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day20::part_2("../2019/day20/input.in") << std::endl;

    return 0;
}
#endif
