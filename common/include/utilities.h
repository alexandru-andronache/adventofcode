#pragma once

#include <string>
#include <vector>

namespace utils {
    struct point {
        int x;
        int y;
    };

    bool isInteger(std::string_view str);
    int getNumber(std::string_view str, int& pos);
    std::vector<std::string> splitString(std::string_view str, std::string_view delimeters);
    std::vector<int> splitStringToInt(std::string_view str, std::string_view delimeters);
    int decimalToInt(std::string_view str, char character = '1');
    int decimalToInt(const std::vector<bool>& str, bool defaultValue = true);
    int manhattanDistance(int x1, int y1, int x2, int y2);
}
