#include "file.h"
#include "utilities.h"
#include "grid.h"
#include "direction.h"
#include <iostream>
#include <set>
#include <deque>

namespace aoc2019_day24 {
    unsigned long long calculateBiodiversity(const std::vector<std::vector<bool>>& board) {
        unsigned long long power = 1;
        unsigned long long res = 0;
        for (const auto& line : board) {
            for (const auto& c : line) {
                if (c) {
                    res += power;
                }
                power *= 2;
            }
        }
        return res;
    }

    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::vector<bool>> board(lines.size(), std::vector<bool>(lines[0].size(), false));
        std::set<unsigned long long> states;
        for (int i = 0; i < lines.size(); ++i) {
            for (int j = 0; j < lines[0].size(); ++j) {
                board[i][j] = lines[i][j] == '#';
            }
        }
        states.insert(calculateBiodiversity(board));

        while (true) {
            std::vector<std::vector<bool>> newBoard(lines.size(), std::vector<bool>(lines[0].size(), false));
            for (int i = 0; i < board.size(); ++i) {
                for (int j = 0; j < board[0].size(); ++j) {
                    int neighbours = grid::numberOfNeighbors4Directions(board, i, j, true);
                    if (board[i][j] && neighbours != 1) {
                        newBoard[i][j] = false;
                    }
                    else if (!board[i][j] && (neighbours == 2 || neighbours == 1)) {
                        newBoard[i][j] = true;
                    }
                    else {
                        newBoard[i][j] = board[i][j];
                    }
                }
            }

            unsigned long long t = calculateBiodiversity(newBoard);
            if (states.count(t) == 1) {
                return t;
            }
            states.insert(t);
            board = newBoard;
        }
    }

    int part_2(std::string_view path, int minutes = 200) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::deque<std::vector<std::vector<bool>>> board(1, std::vector<std::vector<bool>>(lines.size(), std::vector<bool>(lines[0].size(), false)));
//        std::vector<std::vector<std::vector<bool>>> board(300, std::vector<std::vector<bool>>(lines.size(), std::vector<bool>(lines[0].size(), false)));
        for (int i = 0; i < lines.size(); ++i) {
            for (int j = 0; j < lines[0].size(); ++j) {
                board[0][i][j] = lines[i][j] == '#';
            }
        }

        for (int minute = 0; minute < minutes; ++minute) {
            // if top level has any bugs add another level
            if (calculateBiodiversity(board.front()) > 0) {
                board.emplace_front(lines.size(), std::vector<bool>(lines[0].size(), false));
            }
            if (calculateBiodiversity(board.back()) > 0) {
                board.emplace_back(lines.size(), std::vector<bool>(lines[0].size(), false));
            }

            std::deque<std::vector<std::vector<bool>>> newBoard = board;

            for (int i = 0; i < board.size(); ++i) {
                int j = 0;
                for (int k = 0; k < 5; ++k) {
                    // board[i][0][k]
                    /*
                    * [i][0][0] - [i][0][1], [i][1][0], [i - 1][2][1], [i - 1][1][3]
                    * [i][0][1] - [i][0][0], [i][0][2], [i][1][1], [i - 1][1][3]
                    * [i][0][2] - [i][0][1], [i][0][3], [i][1][2], [i - 1][1][3]
                    * [i][0][3] - [i][0][2], [i][0][4], [i][1][3], [i - 1][1][3]
                    * [i][0][4] - [i][0][3], [i][1][4], [i - 1][2][3], [i - 1][1][3]
                    */
                    int neighbours = 0;
                    if (i > 0) {
                        neighbours += board[i - 1][1][2];
                    }

                    for (const auto& dir : direction::directions) {
                        if (j + dir.x >= 0 && j + dir.x <= 4 &&
                            k + dir.y >= 0 && k + dir.y <= 4) {
                            neighbours += board[i][j + dir.x][k + dir.y];
                        }
                    }
                    if (k == 0 && i > 0) {
                        neighbours += board[i - 1][2][1];
                    }
                    else if (k == 4 && i > 0) {
                        neighbours += board[i - 1][2][3];
                    }

                    if (board[i][j][k] && neighbours != 1) {
                        newBoard[i][j][k] = false;
                    }
                    else if (!board[i][j][k] && (neighbours == 2 || neighbours == 1)) {
                        newBoard[i][j][k] = true;
                    }
                    else {
                        newBoard[i][j][k] = board[i][j][k];
                    }
                }

                j = 1;
                for (int k = 0; k < 5; ++k) {
                    // board[i][1][k]
                    /*
                     * [i][1][0] - [i][0][0], [i][1][1], [i][2][0], [i - 1][2][1]
                     * [i][1][1] - [i] +/- 1
                     * [i][1][2] - [i][1][1], [i][1][3], [i][0][2], [i + 1][0][0]-> ...[0][4]
                     * [i][1][3] - [i] +/- 1
                     * [i][1][4] - [i][1][3], [i][0][4], [i][2][4], [i - 1][2][3]
                     */
                    int neighbours = 0;
                    for (const auto& dir : direction::directions) {
                        if (j + dir.x >= 0 && j + dir.x <= 4 &&
                            k + dir.y >= 0 && k + dir.y <= 4) {
                            neighbours += board[i][j + dir.x][k + dir.y];
                        }
                    }
                    if (k == 0 && i > 0) {
                        neighbours += board[i - 1][2][1];
                    }
                    else if (k == 4 && i > 0) {
                        neighbours += board[i - 1][2][3];
                    }
                    else if (k == 2) {
                        if (i + 1 < board.size()) {
                            for (int l = 0; l < 5; ++l) {
                                neighbours += board[i + 1][0][l];
                            }
                        }
                    }

                    if (board[i][j][k] && neighbours != 1) {
                        newBoard[i][j][k] = false;
                    }
                    else if (!board[i][j][k] && (neighbours == 2 || neighbours == 1)) {
                        newBoard[i][j][k] = true;
                    }
                    else {
                        newBoard[i][j][k] = board[i][j][k];
                    }
                }

                j = 2;
                for (int k = 0; k < 5; ++k) {
                    // board[i][2][k]
                    /*
                     * [i][2][0] - [i - 1][2][1]
                     * [i][2][1] - [i] +/- 1, [i + 1][0][0] -> [4][0]
                     * [i][2][2] - no
                     * [i][2][3] - [i] +/- 1, [i + 1][0][4] -> [4][4]
                     * [i][2][4] - [i - 1][2][3]
                     */

                    int neighbours = 0;
                    for (const auto& dir : direction::directions) {
                        if (j + dir.x >= 0 && j + dir.x <= 4 &&
                            k + dir.y >= 0 && k + dir.y <= 4) {
                            neighbours += board[i][j + dir.x][k + dir.y];
                        }
                    }

                    if (k == 0 && i > 0) {
                        neighbours += board[i - 1][2][1];
                    }
                    else if (k == 4 && i > 0) {
                        neighbours += board[i - 1][2][3];
                    }
                    else if (k == 1) {
                        if (i + 1 < board.size()) {
                            for (int l = 0; l < 5; ++l) {
                                neighbours += board[i + 1][l][0];
                            }
                        }
                    }
                    else if (k == 3) {
                        if (i + 1 < board.size()) {
                            for (int l = 0; l < 5; ++l) {
                                neighbours += board[i + 1][l][4];
                            }
                        }
                    }

                    if (board[i][j][k] && neighbours != 1) {
                        newBoard[i][j][k] = false;
                    }
                    else if (!board[i][j][k] && (neighbours == 2 || neighbours == 1)) {
                        newBoard[i][j][k] = true;
                    }
                    else {
                        newBoard[i][j][k] = board[i][j][k];
                    }

                    newBoard[i][j][2] = false;
                }

                j = 3;
                for (int k = 0; k < 5; ++k) {
                    // board[i][3][k]
                    /*
                     * [i][3][0] - [i - 1][2][1]
                     * [i][3][1] - [i] +/- 1
                     * [i][3][2] - [i] +/- 1, [i + 1][4][0] -> [4][4]
                     * [i][3][3] - [i] +/- 1
                     * [i][3][4] - [i] +/- 1, [i - 1][2][3]
                     */

                    int neighbours = 0;
                    for (const auto& dir : direction::directions) {
                        if (j + dir.x >= 0 && j + dir.x <= 4 &&
                            k + dir.y >= 0 && k + dir.y <= 4) {
                            neighbours += board[i][j + dir.x][k + dir.y];
                        }
                    }

                    if (k == 0 && i > 0) {
                        neighbours += board[i - 1][2][1];
                    }
                    else if (k == 4 && i > 0) {
                        neighbours += board[i - 1][2][3];
                    }
                    else if (k == 2) {
                        if (i + 1 < board.size()) {
                            for (int l = 0; l < 5; ++l) {
                                neighbours += board[i + 1][4][l];
                            }
                        }
                    }

                    if (board[i][j][k] && neighbours != 1) {
                        newBoard[i][j][k] = false;
                    }
                    else if (!board[i][j][k] && (neighbours == 2 || neighbours == 1)) {
                        newBoard[i][j][k] = true;
                    }
                    else {
                        newBoard[i][j][k] = board[i][j][k];
                    }
                }

                j = 4;
                for (int k = 0; k < 5; ++k) {
                    // board[i][4][k]
                    /*
                     * [i][4][0] - [i - 1][2][1] + [i - 1][3][2]
                     * [i][4][1] - [i - 1][3][2]
                     * [i][4][2] - [i - 1][3][2]
                     * [i][4][3] - [i - 1][3][2]
                     * [i][4][4] - [i - 1][2][3] + [i - 1][3][2]
                     */

                    int neighbours = 0;
                    if (i > 0) {
                        neighbours += board[i - 1][3][2];
                    }
                    for (const auto& dir : direction::directions) {
                        if (j + dir.x >= 0 && j + dir.x <= 4 &&
                            k + dir.y >= 0 && k + dir.y <= 4) {
                            neighbours += board[i][j + dir.x][k + dir.y];
                        }
                    }

                    if (k == 0 && i > 0) {
                        neighbours += board[i - 1][2][1];
                    }
                    else if (k == 4 && i > 0) {
                        neighbours += board[i - 1][2][3];
                    }

                    if (board[i][j][k] && neighbours != 1) {
                        newBoard[i][j][k] = false;
                    }
                    else if (!board[i][j][k] && (neighbours == 2 || neighbours == 1)) {
                        newBoard[i][j][k] = true;
                    }
                    else {
                        newBoard[i][j][k] = board[i][j][k];
                    }
                }
            }
            board = newBoard;
        }

        int total = 0;
        for (int i = 0; i < board.size(); ++i) {
            for (int j = 0; j < 5; ++j) {
                for (int k = 0; k < 5; ++k) {
                    if (board[i][j][k]) {
                        total++;
                    }
                }
            }
        }

        return total;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day24::part_1("../2019/day24/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day24::part_2("../2019/day24/input.in") << std::endl;

    return 0;
}
#endif
