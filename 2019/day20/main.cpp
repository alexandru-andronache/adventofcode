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
        std::vector<int> steps;
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

    int gateLevel(const std::vector<std::vector<tile>>& board, int x, int y) {
        if (x == 2 || y == 2 || x == board.size() - 3 || y == board[0].size() - 3) {
            return -1;
        }
        return 1;
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        size_t max = 0;
        for (const auto& line : lines) {
            max = std::max(max, line.size());
        }
        std::vector<std::vector<tile>> board(lines.size(), std::vector<tile>(max, {true, "", {}}));
        std::map<std::string, gate> gates;

        for (int i = 0; i < lines.size(); ++i) {
            for (int j = 0; j < max; ++j) {
                if (lines[i][j] == '.') {
                    board[i][j].wall = false;
                }
                else if (lines[i][j] >= 'A' && lines[i][j] <= 'Z') {
                    if (i + 1 < lines.size() && lines[i + 1][j] >= 'A' && lines[i + 1][j] <= 'Z') {
                        if (i + 2 < lines.size() && lines[i + 2][j] == '.') {
                            board[i + 2][j].gate = board[i][j].gate + lines[i][j] + lines[i + 1][j];
                            board[i + 2][j].wall = false;
                        }
                        else if (i > 0) {
                            board[i - 1][j].gate = board[i + 1][j].gate + lines[i][j] + lines[i + 1][j];
                            board[i - 1][j].wall = false;
                        }
                    }
                    else if (j + 1 < max && lines[i][j + 1] >= 'A' && lines[i][j + 1] <= 'Z') {
                        if (j + 2 < max && lines[i][j + 2] == '.') {
                            board[i][j + 2].gate = board[i][j].gate + lines[i][j] + lines[i][j + 1];
                            board[i][j + 2].wall = false;
                        }
                        else if (j > 0) {
                            board[i][j - 1].gate = board[i][j + 1].gate + lines[i][j] + lines[i][j + 1];
                            board[i][j - 1].wall = false;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                board[i][j].steps.push_back(std::numeric_limits<int>::max());
            }
        }

        std::vector<point> positions;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j].gate == "AA") {
                    positions.emplace_back(i, j, 0);
                    board[i][j].steps[0] = 0;
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
                    if (pos.x + direction.x >= 0 && pos.x + direction.x < board.size() &&
                        pos.y + direction.y >= 0 && pos.y + direction.y < board[0].size() &&
                        !board[pos.x + direction.x][pos.y + direction.y].wall &&
                        board[pos.x + direction.x][pos.y + direction.y].steps[0] > board[pos.x][pos.y].steps[0] + 1) {
                        if (board[pos.x + direction.x][pos.y + direction.y].gate.empty()) {
                            board[pos.x + direction.x][pos.y + direction.y].steps[0] = board[pos.x][pos.y].steps[0] + 1;
                            newPositions.emplace_back(pos.x + direction.x, pos.y + direction.y, 0);
                        }
                        else {
                            board[pos.x + direction.x][pos.y + direction.y].steps[0] = board[pos.x][pos.y].steps[0] + 1;
                            if (board[pos.x + direction.x][pos.y + direction.y].gate != "ZZ") {
                                auto gatePositions = gates[board[pos.x + direction.x][pos.y + direction.y].gate];
                                if (pos.x + direction.x == gatePositions.p1.x &&
                                    pos.y + direction.y == gatePositions.p1.y) {
                                    if (board[gatePositions.p2.x][gatePositions.p2.y].steps[0] > board[gatePositions.p1.x][gatePositions.p1.y].steps[0] + 1) {
                                        board[gatePositions.p2.x][gatePositions.p2.y].steps[0] = board[gatePositions.p1.x][gatePositions.p1.y].steps[0] + 1;
                                        newPositions.emplace_back(gatePositions.p2.x, gatePositions.p2.y, 0);
                                    }
                                }
                                else {
                                    if (board[gatePositions.p1.x][gatePositions.p1.y].steps[0] > board[gatePositions.p2.x][gatePositions.p2.y].steps[0] + 1) {
                                        board[gatePositions.p1.x][gatePositions.p1.y].steps[0] = board[gatePositions.p2.x][gatePositions.p2.y].steps[0] + 1;
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

        return board[gates["ZZ"].p1.x][gates["ZZ"].p1.y].steps[0];
    }

    int part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        size_t max = 0;
        for (const auto& line : lines) {
            max = std::max(max, line.size());
        }
        std::vector<std::vector<tile>> board(lines.size(), std::vector<tile>(max, {true, "", {}}));
        std::map<std::string, gate> gates;

        for (int i = 0; i < lines.size(); ++i) {
            for (int j = 0; j < max; ++j) {
                if (lines[i][j] == '.') {
                    board[i][j].wall = false;
                }
                else if (lines[i][j] >= 'A' && lines[i][j] <= 'Z') {
                    if (i + 1 < lines.size() && lines[i + 1][j] >= 'A' && lines[i + 1][j] <= 'Z') {
                        if (i + 2 < lines.size() && lines[i + 2][j] == '.') {
                            board[i + 2][j].gate = board[i][j].gate + lines[i][j] + lines[i + 1][j];
                            board[i + 2][j].wall = false;
                        }
                        else if (i > 0) {
                            board[i - 1][j].gate = board[i + 1][j].gate + lines[i][j] + lines[i + 1][j];
                            board[i - 1][j].wall = false;
                        }
                    }
                    else if (j + 1 < max && lines[i][j + 1] >= 'A' && lines[i][j + 1] <= 'Z') {
                        if (j + 2 < max && lines[i][j + 2] == '.') {
                            board[i][j + 2].gate = board[i][j].gate + lines[i][j] + lines[i][j + 1];
                            board[i][j + 2].wall = false;
                        }
                        else if (j > 0) {
                            board[i][j - 1].gate = board[i][j + 1].gate + lines[i][j] + lines[i][j + 1];
                            board[i][j - 1].wall = false;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
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

        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                board[i][j].steps.insert(board[i][j].steps.end(), gates.size(), std::numeric_limits<int>::max());
            }
        }

        std::vector<point> positions;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < board[0].size(); ++j) {
                if (board[i][j].gate == "AA") {
                    positions.emplace_back(i, j, 0);
                    board[i][j].steps[0] = 0;
                }
            }
        }

        while (!positions.empty()) {
            std::vector<point> newPositions;
            for (const auto& pos : positions) {
                for (const auto& direction : direction::directions) {
                    if (pos.x + direction.x >= 0 && pos.x + direction.x < board.size() &&
                        pos.y + direction.y >= 0 && pos.y + direction.y < board[0].size() &&
                        !board[pos.x + direction.x][pos.y + direction.y].wall &&
                        board[pos.x + direction.x][pos.y + direction.y].steps[pos.depth] > board[pos.x][pos.y].steps[pos.depth] + 1) {
                        if (board[pos.x + direction.x][pos.y + direction.y].gate.empty()) {
                            board[pos.x + direction.x][pos.y + direction.y].steps[pos.depth] = board[pos.x][pos.y].steps[pos.depth] + 1;
                            newPositions.emplace_back(pos.x + direction.x, pos.y + direction.y, pos.depth);
                        }
                        else {
                            board[pos.x + direction.x][pos.y + direction.y].steps[pos.depth] = board[pos.x][pos.y].steps[pos.depth] + 1;
                            if (board[pos.x + direction.x][pos.y + direction.y].gate != "ZZ") {
                                auto gatePositions = gates[board[pos.x + direction.x][pos.y + direction.y].gate];
                                if (pos.x + direction.x == gatePositions.p1.x &&
                                    pos.y + direction.y == gatePositions.p1.y) {
                                    if ((pos.depth + gateLevel(board, gatePositions.p1.x, gatePositions.p1.y) >= 0) &&
                                        board[gatePositions.p2.x][gatePositions.p2.y].steps[pos.depth + gateLevel(board, gatePositions.p1.x, gatePositions.p1.y)] > board[gatePositions.p1.x][gatePositions.p1.y].steps[pos.depth + gateLevel(board, gatePositions.p1.x, gatePositions.p1.y)] + 1) {
                                        board[gatePositions.p2.x][gatePositions.p2.y].steps[pos.depth + gateLevel(board, gatePositions.p1.x, gatePositions.p1.y)] = board[gatePositions.p1.x][gatePositions.p1.y].steps[pos.depth] + 1;
                                        newPositions.emplace_back(gatePositions.p2.x, gatePositions.p2.y, pos.depth + gateLevel(board, gatePositions.p1.x, gatePositions.p1.y));
                                    }
                                }
                                else {
                                    if ((pos.depth + gateLevel(board, gatePositions.p2.x, gatePositions.p2.y)  >= 0) &&
                                        board[gatePositions.p1.x][gatePositions.p1.y].steps[pos.depth + gateLevel(board, gatePositions.p2.x, gatePositions.p2.y)] > board[gatePositions.p2.x][gatePositions.p2.y].steps[pos.depth + gateLevel(board, gatePositions.p2.x, gatePositions.p2.y)] + 1) {
                                        board[gatePositions.p1.x][gatePositions.p1.y].steps[pos.depth + gateLevel(board, gatePositions.p2.x, gatePositions.p2.y)] = board[gatePositions.p2.x][gatePositions.p2.y].steps[pos.depth] + 1;
                                        newPositions.emplace_back(gatePositions.p1.x, gatePositions.p1.y, pos.depth + gateLevel(board, gatePositions.p2.x, gatePositions.p2.y));
                                    }
                                }
                            }
                        }
                    }
                }
            }
            positions = newPositions;
        }

        return board[gates["ZZ"].p1.x][gates["ZZ"].p1.y].steps[0];
    }

}


#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day20::part_1("../2019/day20/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day20::part_2("../2019/day20/input.in") << std::endl;

    return 0;
}
#endif
