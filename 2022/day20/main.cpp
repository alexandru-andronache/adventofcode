#include "file.h"
#include "utilities.h"
#include <iostream>
#include <cmath>
#include <optional>
#include <deque>

namespace aoc2022_day20 {
    int part_1(std::string_view path) {
        std::vector<int> nr = file::readFileAsArrayInt(path);
        std::vector<int> pos;
        for (int i = 0; i < nr.size(); ++i) {
            pos.push_back(i);
        }

        int s = nr.size();
        for (int i = 0; i < nr.size(); ++i) {
            int oldPos = pos[i];
            int newPos = (pos[i] + nr[i]) % (s - 1);
        }
    }

    int part_2(std::string_view path) {
        return 0;
    }

}


#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2022_day20::part_1("../2022/day20/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2022_day20::part_2("../2022/day20/input.in") << std::endl;

    return 0;
}
#endif


//#include <algorithm>
////#include <fmt/format.h>
//#include <fstream>
//#include <iostream>
//#include <list>
//#include <ranges>
//#include <string>
//#include <vector>
//
////#include "simpleparser.hpp"
//
////using std::views::iota;
//
//std::vector<int64_t> data{};
//std::vector<int64_t> position{};
//
//int64_t dataAt(const int64_t pos) {
//    for (int i = 0; i < position.size(); ++i) {
////    for (const auto i : iota(0, (int64_t)position.size())) {
//        if (position[i] == pos % (int64_t)position.size())
//            return data[i];
//    }
//    std::cout << "dataAt " << pos << "\n";
////    fmt::print("dataAt({})\n", pos);
////    throw("not reached");
//}
//
////void printData() {
////    fmt::print("{}", dataAt(0));
////    for (const auto pos : iota(1, (int64_t)position.size())) {
////        fmt::print(", {}", dataAt(pos));
////    }
////    // fmt::print("  [{}",position[0]);
////    // for(const auto &pos : position | std::views::drop(1)) {
////    //     fmt::print(", {}", pos);
////    // }
////    fmt::print("\n");
////}
//
//void mix() {
//    const auto modulus = (int64_t)data.size();
//    for (int i = 0; i < modulus; ++i) {
////    for (const auto i : iota(0, modulus)) {
//        if (data[i] % (modulus - 1) == 0)
//            continue;
//        const auto oldPos = position[i];
//        const auto newRawPos = oldPos + data[i] % (modulus - 1);
//        const auto newPos = [&]() {
//            if (0 < newRawPos and newRawPos < modulus)
//                return newRawPos;
//            if (newRawPos <= 0)
//                return newRawPos + modulus - 1;
//            return newRawPos - modulus + 1;
//        }();
//        for (auto &ele : position) {
//            if (oldPos < newPos and oldPos <= ele and ele <= newPos) {
//                ele = (ele - 1 + modulus) % modulus;
//            } else if (newPos < oldPos and newPos <= ele and ele <= oldPos) {
//                ele = (ele + 1) % modulus;
//            }
//        }
//        position[i] = newPos;
//        // printData();
//    }
//}
//
//int main(int argc, char **argv) {
////    if (argc < 2) {
////        std::cerr << "Usage: " << argv[0] << " <input.txt> [decryption key]\n";
////        std::exit(EXIT_FAILURE);
////    }
//
////    int64_t DECRYPTION_KEY{811589153};
//    int64_t DECRYPTION_KEY{1};
//    if (argc == 3) {
//        DECRYPTION_KEY = std::stol(argv[2]);
//    }
//
////    SimpleParser scanner{argv[1]};
//    std::vector<int> pos = file::readFileAsArrayInt("../2022/day20/input_test.in");
//    int64_t index = 0;
//    int64_t zeroPos = 0;
////    while (!scanner.isEof()) {
////        data.push_back(scanner.getInt64() * DECRYPTION_KEY);
////        if (data.back() == 0) {
////            zeroPos = index;
////        }
////        position.push_back(index);
////        ++index;
////    }
//
//    for (int i = 0; i < pos.size(); ++i) {
//        data.push_back(pos[i] * DECRYPTION_KEY);
//        if (data.back() == 0) {
//            zeroPos = index;
//        }
//        position.push_back(index);
//        ++index;
//    }
//    // printData();
//    mix();
//    if (DECRYPTION_KEY != 1) {
//        for (int i = 0; i < 9; ++i) {
//            mix();
//        }
//    }
//    // printData();
//    const auto d1000 = dataAt(1000 + position[zeroPos]);
//    const auto d2000 = dataAt(2000 + position[zeroPos]);
//    const auto d3000 = dataAt(3000 + position[zeroPos]);
//    std::cout << d1000 + d2000 + d3000;
////    fmt::print(
////            "Deciffering vector [{}, {}, {}]\nDecrypted grove coordinates are {}\n",
////            d1000, d2000, d3000, d1000 + d2000 + d3000);
//}
