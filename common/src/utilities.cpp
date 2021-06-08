#include "utilities.h"

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
    int decimalToInt(std::string_view str, char character) {
        int nr = 0;
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
}