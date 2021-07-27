#include "file.h"
#include "utilities.h"
#include <iostream>
#include <sstream>
#include <array>

namespace aoc2017_day10 {
    int part_1(std::string_view path, int size = 256) {
        std::vector<int> input = utils::splitStringToInt(file::readFileAsString(path), ",");

        int currentPosition = 0;
        int skip = 0;
        std::vector<int> list;
        for (int i = 0; i < size; ++i) {
            list.push_back(i);
        }

        for (const auto& x : input) {
            for (int i = 0; i < x / 2; ++i) {
                std::swap(list[(currentPosition + i) % size], list[(currentPosition - i + x - 1) % size]);
            }
            currentPosition = (currentPosition +  x + skip) % size;
            skip++;
        }

        return list[0] * list[1];
    }

    std::string part_2(std::string_view path, int size = 256, int rounds = 64) {
        std::vector<int> input = utils::splitStringToInt(file::readFileAsString(path), ",");

        int currentPosition = 0;
        int skip = 0;
        std::vector<int> list;
        for (int i = 0; i < size; ++i) {
            list.push_back(i);
        }
        std::vector<int> lengths;
        for (auto x : input) {
            std::vector<int> numbers;
            numbers.push_back(x % 10 + '0');
            x = x / 10;
            while (x > 0) {
                numbers.push_back(x % 10 + '0');
                x = x / 10;
            }
            std::reverse(numbers.begin(), numbers.end());
            lengths.insert(lengths.end(), numbers.begin(), numbers.end());
            lengths.push_back(44); // ascii code for ,
        }
        lengths.pop_back();
        lengths.insert(lengths.end(), {17, 31, 73, 47, 23});

        for (int r = 0; r < rounds; ++r) {
            for (const auto& x : lengths) {
                for (int i = 0; i < x / 2; ++i) {
                    std::swap(list[(currentPosition + i) % size], list[(currentPosition - i + x - 1) % size]);
                }
                currentPosition = (currentPosition +  x + skip) % size;
                skip++;
            }
        }

        std::vector<int> output(16, 0);
        for (int i = 0; i < 16; ++i) {
            output[i] = list[i * 16];
            for (int j = 1; j < 16; ++j) {
                output[i] = output[i] ^ list[i * 16 + j];
            }
        }

        std::stringstream stream;
        for (int i = 0; i < 16; ++i) {
            stream << std::hex << output[i];
        }
        std::string result(stream.str());

        return result;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2017_day10::part_1("../2017/day10/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2017_day10::part_2("../2017/day10/input.in") << std::endl;

    return 0;
}
#endif
