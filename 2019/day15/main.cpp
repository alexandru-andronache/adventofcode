#include "file.h"
#include "intcode.h"
#include <iostream>
#include <vector>

namespace aoc2019_day15 {
    enum class StatusCode {
        Wall = 0,
        Move = 1,
        MoveOxygen = 2
    };
    enum class Room {
        Empty = 0,
        Visited = 1,
        Wall = 2
    };

    const int SIZE = 100;
    std::vector<std::vector<Room>> board(SIZE, std::vector<Room>(SIZE, Room::Empty));
    std::vector<std::vector<int>> distance(SIZE, std::vector<int>(SIZE, -1));
    std::vector<std::vector<int>> distanceFromOxygen(SIZE, std::vector<int>(SIZE, -1));
    std::vector<std::pair<int, int>> directions {{-1, 0}, {1, 0}, {0, -1}, {0,1}};
    int oxygenX = 0, oxygenY = 0;

    void move(intcode::IntCode<unsigned long long>& calc, int droidPosX, int droidPosY) {
        for (int i = 0; i < directions.size(); ++i) {
            if (board[droidPosX + directions[i].first][droidPosY + directions[i].second] == Room::Empty) {
                calc.inputIDs.push_back(i + 1);
                auto exit = calc.advance();
                if (exit.returnValue == (int)StatusCode::Wall) {
                    board[droidPosX + directions[i].first][droidPosY + directions[i].second] = Room::Wall;
                }
                else {
                    droidPosX += directions[i].first;
                    droidPosY += directions[i].second;
                    board[droidPosX][droidPosY] = Room::Visited;
                    if (exit.returnValue == (int)StatusCode::MoveOxygen) {
                        oxygenX = droidPosX;
                        oxygenY = droidPosY;
                    }
                    move(calc, droidPosX, droidPosY);
                    calc.inputIDs.push_back((i + 1) % 2 + i - i % 2 + 1);
                    calc.advance();
                    droidPosX += directions[(i + 1) % 2 + i - i % 2].first;
                    droidPosY += directions[(i + 1) % 2 + i - i % 2].second;
                }
            }
        }
    }

    void calculateDist(int startX, int startY) {
        int d = distance[startX][startY];
        for (const auto & direction : directions) {
            if (board[startX + direction.first][startY + direction.second] != Room::Wall &&
            (distance[startX + direction.first][startY + direction.second] == -1 ||
            distance[startX + direction.first][startY + direction.second] + 1 < d)) {
                distance[startX + direction.first][startY + direction.second] = d + 1;
                calculateDist(startX + direction.first, startY + direction.second);
            }
        }
    }

    void calculateDistFromOxygen(int startX, int startY) {
        int d = distanceFromOxygen[startX][startY];
        for (const auto& dir : directions) {
            if (board[startX + dir.first][startY + dir.second] != Room::Wall &&
            (distanceFromOxygen[startX + dir.first][startY + dir.second] == -1 ||
            distanceFromOxygen[startX + dir.first][startY + dir.second] + 1 < d)) {
                distanceFromOxygen[startX + dir.first][startY + dir.second] = d + 1;
                calculateDistFromOxygen(startX + dir.first, startY + dir.second);
            }
        }
    }

    int part_1(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");

        intcode::IntCode<unsigned long long>calc{input, {}};
        int droidPosX = SIZE / 2, droidPosY = SIZE / 2;
        move(calc, droidPosX, droidPosY);

        distance[SIZE / 2][SIZE / 2] = 0;
        calculateDist(SIZE / 2, SIZE / 2);

        return  distance[oxygenX][oxygenY];
    }

    int part_2(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");

        intcode::IntCode<unsigned long long>calc{input, {}};
        int droidPosX = SIZE / 2, droidPosY = SIZE / 2;
        for (auto& line : board) {
            for (auto& c : line) {
                c = Room::Empty;
            }
        }
        move(calc, droidPosX, droidPosY);

        distanceFromOxygen[oxygenX][oxygenY] = 0;
        calculateDistFromOxygen(oxygenX, oxygenY);

        int max = 0;
        for (const auto& line : distanceFromOxygen) {
            for (const auto& c : line) {
                max = std::max(c, max);
            }
        }

        return max;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day15::part_1("../2019/day15/input.in") << std::endl;
    std::cout << "Part 1: " << aoc2019_day15::part_2("../2019/day15/input.in") << std::endl;

    return 0;
}
#endif
