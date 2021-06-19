#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>
#include <numeric>

namespace aoc2016_day08 {
    enum class Type {
        Fill,
        RotateRow,
        RotateColumn
    };

    struct Operation {
        Type type;
        int x;
        int y;
    };

    int part_1(std::string_view path) {
        const int width = 50;
        const int height = 6;

        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<Operation> operations;
        for (const auto& line : lines) {
            std::vector<std::string> s = utils::splitString(line, " =");
            Operation op;
            if (s[0] == "rect") {
                op.type = Type::Fill;
                op.x = op.y = 0;
                int i = 0;
                while (s[1][i] != 'x') {
                    op.x = op.x * 10 + s[1][i] - '0';
                    i++;
                }
                i++;
                while (i < s[1].size()) {
                    op.y = op.y * 10 + s[1][i] - '0';
                    i++;
                }
            }
            else if (s[1] == "row") {
                op.type = Type::RotateRow;
                op.x = atoi(s[3].c_str());
                op.y = atoi(s[5].c_str());
            }
            else {
                op.type = Type::RotateColumn;
                op.x = atoi(s[3].c_str());
                op.y = atoi(s[5].c_str());
            }
            operations.emplace_back(op);
        }


        std::vector<std::vector<bool>> board(height, std::vector<bool>(width, false));

        for (const auto& op : operations) {
            std::vector<bool> line(width, false);
            std::vector<bool> column(height, false);
            switch (op.type) {
                case Type::Fill:
                    for (int i = 0; i < op.y; ++i) {
                        for (int j = 0; j < op.x; ++j) {
                            board[i][j] = true;
                        }
                    }
                    break;
                    case Type::RotateRow:
                        for (int i = 0; i < width; ++i) {
                            line[(i + op.y) % width] = board[op.x][i];
                        }
                        for (int i = 0; i < width; ++i) {
                            board[op.x][i] = line[i];
                        }
                        break;
                        case Type::RotateColumn:
                            for (int i = 0; i < height; ++i) {
                                column[(i + op.y) % height] = board[i][op.x];
                            }
                            for (int i = 0; i < height; ++i) {
                                board[i][op.x] = column[i];
                            }
                            break;
            }
        }

        int sum = 0;
        for (int i = 0; i < height; ++i) {
            sum += std::accumulate(board[i].begin(), board[i].end(), 0);
        }
        return sum;
    }

    void part_2(std::string_view path) {
        const int width = 50;
        const int height = 6;

        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<Operation> operations;
        for (const auto& line : lines) {
            std::vector<std::string> s = utils::splitString(line, " =");
            Operation op;
            if (s[0] == "rect") {
                op.type = Type::Fill;
                op.x = op.y = 0;
                int i = 0;
                while (s[1][i] != 'x') {
                    op.x = op.x * 10 + s[1][i] - '0';
                    i++;
                }
                i++;
                while (i < s[1].size()) {
                    op.y = op.y * 10 + s[1][i] - '0';
                    i++;
                }
            }
            else if (s[1] == "row") {
                op.type = Type::RotateRow;
                op.x = atoi(s[3].c_str());
                op.y = atoi(s[5].c_str());
            }
            else {
                op.type = Type::RotateColumn;
                op.x = atoi(s[3].c_str());
                op.y = atoi(s[5].c_str());
            }
            operations.emplace_back(op);
        }


        std::vector<std::vector<bool>> board(height, std::vector<bool>(width, false));

        for (const auto& op : operations) {
            std::vector<bool> line(width, false);
            std::vector<bool> column(height, false);
            switch (op.type) {
                case Type::Fill:
                    for (int i = 0; i < op.y; ++i) {
                        for (int j = 0; j < op.x; ++j) {
                            board[i][j] = true;
                        }
                    }
                    break;
                    case Type::RotateRow:
                        for (int i = 0; i < width; ++i) {
                            line[(i + op.y) % width] = board[op.x][i];
                        }
                        for (int i = 0; i < width; ++i) {
                            board[op.x][i] = line[i];
                        }
                        break;
                        case Type::RotateColumn:
                            for (int i = 0; i < height; ++i) {
                                column[(i + op.y) % height] = board[i][op.x];
                            }
                            for (int i = 0; i < height; ++i) {
                                board[i][op.x] = column[i];
                            }
                            break;
            }
        }

        std::cout << std::endl;
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (board[i][j]) {
                    std::cout << "#";
                }
                else {
                    std::cout << " ";
                }
            }
            std::cout << std::endl;
        }
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day08::part_1("../2016/day08/input.in") << std::endl;
    std::cout << "Part 2: " << std::endl;
    aoc2016_day08::part_2("../2016/day08/input.in");

    return 0;
}
#endif
