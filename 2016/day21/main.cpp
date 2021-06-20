#include "file.h"
#include "utilities.h"
#include <iostream>

namespace aoc2016_day21 {

    std::string rotateToRight(std::string str, int nr) {
        for (int i = 0; i < nr; ++i) {
            std::string extra(1, str.back());
            str.erase(str.size() - 1, 1);
            str.insert(0, extra);
        }
        return str;
    }

    std::string rotateToLeft(std::string str, int nr) {
        for (int i = 0; i < nr; ++i) {
            std::string extra(1, str[0]);
            str.erase(0, 1);
            str.insert(str.size(), extra);
        }
        return str;
    }

    std::string part_1(std::string_view path, std::string str) {
        std::vector<std::string> file = file::readFileAsArrayString(path);
        std::vector<std::vector<std::string>> input;
        for (const auto& line : file) {
            input.push_back(utils::splitString(line, " "));
        }

        for (const auto& line : input) {
            if (line[0] == "swap" && line[1] == "position") {
                std::swap(str[atoi(line[2].c_str())], str[atoi(line[5].c_str())]);
            }
            else if (line[0] == "swap" && line[1] == "letter") {
                int x = std::distance(str.begin(), std::find(str.begin(), str.end(), line[2][0]));
                int y = std::distance(str.begin(), std::find(str.begin(), str.end(), line[5][0]));
                std::swap(str[x], str[y]);
            }
            else if (line[0] == "rotate" && line[1] == "right") {
                str = rotateToRight(str, atoi(line[2].c_str()));
            }
            else if (line[0] == "rotate" && line[1] == "left") {
                str = rotateToLeft(str, atoi(line[2].c_str()));
            }
            else if (line[0] == "reverse") {
                std::reverse(str.begin() + atoi(line[2].c_str()), str.begin() + atoi(line[4].c_str()) + 1);
            }
            else if (line[0] == "move") {
                int x = atoi(line[2].c_str());
                int y = atoi(line[5].c_str());
                std::string l(1, str[x]);
                str.erase(x, 1);
                str.insert(y, l);
            }
            else {
                int index = std::distance(str.begin(), std::find(str.begin(), str.end(), line[6][0]));
                if (index >= 4) {
                    index++;
                }
                index++;
                str = rotateToRight(str, index);
            }
        }
        return str;
    }

    std::string part_2(std::string_view path, std::string str) {
        std::vector<std::string> file = file::readFileAsArrayString(path);
        std::vector<std::vector<std::string>> input;
        for (const auto& line : file) {
            input.push_back(utils::splitString(line, " "));
        }

        for (auto it = input.rbegin(); it != input.rend(); ++it) {
            if ((*it)[0] == "swap" && (*it)[1] == "position") {
                std::swap(str[atoi((*it)[2].c_str())], str[atoi((*it)[5].c_str())]);
            }
            else if ((*it)[0] == "swap" && (*it)[1] == "letter") {
                int x = std::distance(str.begin(), std::find(str.begin(), str.end(), (*it)[2][0]));
                int y = std::distance(str.begin(), std::find(str.begin(), str.end(), (*it)[5][0]));
                std::swap(str[x], str[y]);
            }
            else if ((*it)[0] == "rotate" && (*it)[1] == "right") {
                str = rotateToLeft(str, atoi((*it)[2].c_str()));
            }
            else if ((*it)[0] == "rotate" && (*it)[1] == "left") {
                str = rotateToRight(str, atoi((*it)[2].c_str()));
            }
            else if ((*it)[0] == "reverse") {
                std::reverse(str.begin() + atoi((*it)[2].c_str()), str.begin() + atoi((*it)[4].c_str()) + 1);
            }
            else if ((*it)[0] == "move") {
                int y = atoi((*it)[2].c_str());
                int x = atoi((*it)[5].c_str());
                std::string l(1, str[x]);
                str.erase(x, 1);
                str.insert(y, l);
            }
            else {
                int index = 0;
                int r = 0;
                do {
                    str = rotateToLeft(str, 1);
                    index = std::distance(str.begin(), std::find(str.begin(), str.end(), (*it)[6][0]));
                    r++;
                    if(index >= 4) {
                        index++;
                    }
                    index++;
                }
                while (index != r);
            }
        }
        return str;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2016_day21::part_1("../2016/day21/input.in", "abcdefgh") << std::endl;
    std::cout << "Part 2: " << aoc2016_day21::part_2("../2016/day21/input.in", "fbgdceah") << std::endl;

    return 0;
}
#endif
