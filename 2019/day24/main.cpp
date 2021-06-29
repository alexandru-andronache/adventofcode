#include "file.h"
#include "utilities.h"
#include "grid.h"
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

    unsigned int part_2(std::string_view path, int minutes = 200) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::deque<std::vector<std::vector<bool>>> board(1, std::vector<std::vector<bool>>(lines.size(), std::vector<bool>(lines[0].size(), false)));

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
                for (int j = 0; j < board[i].size(); ++j) {
                    for (int k = 0; k < board[i][j].size(); ++k) {
                        int neighbours = grid::numberOfNeighbors4Directions(board[i], j, k, true);

                        if (j == 0 && i > 0) {
                            neighbours += board[i - 1][1][2];
                        }
                        else if (j == 1 && k == 2 && i + 1 < board.size()) {
                            for (int l = 0; l < 5; ++l) {
                                neighbours += board[i + 1][0][l];
                            }
                        }
                        else if (j == 2 && k == 1 && i + 1 < board.size()) {
                            for (int l = 0; l < 5; ++l) {
                                neighbours += board[i + 1][l][0];
                            }
                        }
                        else if (j == 2 && k == 3 && i + 1 < board.size()) {
                            for (int l = 0; l < 5; ++l) {
                                neighbours += board[i + 1][l][4];
                            }
                        }
                        else if (j == 3 && k == 2 && i + 1 < board.size()) {
                            for (int l = 0; l < 5; ++l) {
                                neighbours += board[i + 1][4][l];
                            }
                        }
                        else if (j == 4 && i > 0) {
                            neighbours += board[i - 1][3][2];
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
                        newBoard[i][2][2] = false;
                    }
                }
            }
            board = newBoard;
        }

        unsigned int total = 0;
        for (const auto& floor : board) {
            for (int j = 0; j < floor.size(); ++j) {
                total += std::count(floor[j].begin(), floor[j].end(), true);
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
