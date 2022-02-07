#include "utilities.h"
#include "direction.h"
#include <array>
#include <algorithm>

namespace utils {

    bool isInteger(std::string_view str) {
        auto it = str.begin();
        if ((*it) == '-') {
            it++;
        }
        return std::all_of(it, str.end(), [](char l) {
            return (l >= '0' && l <= '9');
        });
    }

    /*
     * returns the number found in str starting at the position pos
     */
    int getNumber(std::string_view str, int& pos) {
        int nr = 0;
        bool isNegative = false;
        if (str[pos] == '-') {
            isNegative = true;
            pos++;
        }
        while (pos < str.size() && str[pos] >= '0' && str[pos] <= '9') {
            nr = nr * 10 + str[pos] - '0';
            pos++;
        }
        return isNegative * (-1) * nr + !isNegative * nr;
    }

    std::vector<std::string> splitString(std::string_view str, std::string_view delimeters) {
        std::vector<std::string> output;
        std::size_t prev = 0, pos;
        while ((pos = str.find_first_of(delimeters, prev)) != std::string::npos)
        {
            if (pos > prev)
                output.emplace_back(str.substr(prev, pos - prev));
            prev = pos + 1;
        }
        if (prev < str.length())
            output.emplace_back(str.substr(prev, std::string::npos));

        return output;
    }

    std::vector<int> splitStringToInt(std::string_view str, std::string_view delimeters) {
        std::vector<std::string> output = splitString(str, delimeters);
        std::vector<int> nr(output.size(), 0);
        for (int i = 0; i < output.size(); ++i) {
            nr[i] = std::stoi(output[i]);
        }
        return nr;
    }

    /*
     * return the decimal value of binary string str with 1 being represented by the character
     * typically call this with '1' as default but sometimes the value might be represented by another character
     */
    unsigned long long decimalToInt(std::string_view str, char character) {
        unsigned long long nr = 0;
        for (const auto& c : str) {
            nr *= 2;
            if (c == character) {
                nr++;
            }
        }
        return nr;
    }

    int decimalToInt(const std::vector<bool>&str, bool defaultValue) {
        int nr = 0;
        for (const auto& c : str) {
            nr *= 2;
            if (c == defaultValue) {
                nr++;
            }
        }
        return nr;
    }

    int manhattanDistance(int x1, int y1, int x2, int y2) {
        return std::abs(x1 - x2) + std::abs(y1 - y2);
    }

    bool isAnagram(std::string_view s1, std::string_view s2) {
        if (s1.size() != s2.size()) return false;
        std::array<int, 26> letters;
        letters.fill(0);
        for (const auto& l : s1) {
            letters[l - 'a']++;
        }
        for (const auto& l : s2) {
            letters[l - 'a']--;
        }
        for (const auto& e : letters) {
            if (e != 0) return false;
        }
        return true;
    }

    std::vector<point> getListOfNeighbours4Directions(int x, int y, const std::vector<std::vector<int>>& map) {
        direction::Direction dir;
        std::vector<point> neighbours;
        for (const auto& d : dir.directions) {
            if (x + d.x >= 0 && x + d.x < map.size() && y + d.y >= 0 && y + d.y < map[0].size()) {
                neighbours.push_back({x + d.x, y + d.y});
            }
        }
        return neighbours;
    }

    std::vector<point> getListOfNeighboursAllDirections(int x, int y, const std::vector<std::vector<int>>& map) {
        direction::Direction dir;
        std::vector<point> neighbours;
        for (const auto& d : dir.fullDirections) {
            if (x + d.x >= 0 && x + d.x < map.size() && y + d.y >= 0 && y + d.y < map[0].size()) {
                neighbours.push_back({x + d.x, y + d.y});
            }
        }
        return neighbours;
    }
}