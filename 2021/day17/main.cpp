#include "file.h"
#include "utilities.h"
#include <iostream>
#include <vector>

namespace aoc2021_day17 {
    int part_1(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::vector<std::string> tokens = utils::splitString(input, " : =.,");
        int startX = std::stoi(tokens[3]);
        int endX = std::stoi(tokens[4]);
        int startY = std::stoi(tokens[6]);
        int endY = std::stoi(tokens[7]);
        int sol = std::numeric_limits<int>::min();

        for (int x = 0; x <= endX; ++x) {
            for (int y = startY; y <= 150; ++y) {
                int posX = 0, posY = 0;
                int speedX = x, speedY = y;
                int maxY = std::numeric_limits<int>::min();
                bool wasSolution = false;
                while (posY >= startY && !wasSolution) {
                    posX += speedX;
                    posY += speedY;
                    maxY = std::max(maxY, posY);
                    speedX = std::max(0, speedX - 1);
                    speedY--;
                    if (posX >= startX && posX <= endX && posY >= startY && posY <= endY) {
                        wasSolution = true;
                        sol = std::max(sol, maxY);
                    }
                }
            }
        }

        return sol;
    }

    int part_2(std::string_view path) {
        std::string input = file::readFileAsString(path);
        std::vector<std::string> tokens = utils::splitString(input, " : =.,");
        int startX = std::stoi(tokens[3]);
        int endX = std::stoi(tokens[4]);
        int startY = std::stoi(tokens[6]);
        int endY = std::stoi(tokens[7]);
        int sol = 0;

        for (int x = 0; x <= endX; ++x) {
            for (int y = startY; y <= 150; ++y) {
                int posX = 0, posY = 0;
                int speedX = x, speedY = y;
                bool solution = false;
                while (posY >= startY && !solution) {
                    posX += speedX;
                    posY += speedY;
                    speedX = std::max(0, speedX - 1);
                    speedY--;
                    if (posX >= startX && posX <= endX && posY >= startY && posY <= endY) {
                        sol++;
                        solution = true;
                    }
                }
            }
        }

        return sol;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2021_day17::part_1("../2021/day17/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2021_day17::part_2("../2021/day17/input.in") << std::endl;

    return 0;
}
#endif
