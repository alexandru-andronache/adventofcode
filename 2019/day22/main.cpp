#include "file.h"
#include "utilities.h"
#include <iostream>
#include <numeric>

namespace aoc2019_day22 {
    __int128 normalize(__int128 value, long long modulo) {
        if (value >= 0) {
            return value % modulo;
        }
        return modulo - ((-value) % modulo);
    }

    unsigned int part_1(std::string_view path, int size = 10007, int card = 2019) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        long long A = 0;
        long long B = 0;

        for (int i = 0; i < lines.size(); ++i) {
            std::vector<std::string> words = utils::splitString(lines[i], " ");
            int a = 0, b = 0;
            if (lines[i] == "deal into new stack") {
                a = -1;
                b = size - 1;
            }
            else if (words[0] == "cut") {
                int N = std::stoi(words[1]);
                a = 1;
                b = -N;
            }
            else {
                int N = std::stoi(words[3]);
                a = N;
                b = 0;
            }
            if (i == 0) {
                A = a;
                B = b;
            }
            else {
                B = a * B + b;
                A = A * a;
            }
            A = normalize(A, size);
            B = normalize(B, size);
        }

        return normalize(A * card + B, size);
    }

    __int128_t modinv(__int128_t a, __int128_t b)
    {
        long long b0 = b;
        long long aa = 1, ba = 0;
        while (true)
        {
            long long q = a / b;
            if (a == b * q)
            {
                if (b != 1)
                {
                    // Modular inverse does not exist!
                    return -1;
                }
                while (ba < 0) ba += b0;
                return ba;
            }
            long long tmp_a = a;
            long long tmp_aa = aa;
            a = b;
            b = tmp_a - b * q;
            aa = ba;
            ba = tmp_aa - ba * q;
        }
    }

    __int128_t modular_divide(__int128_t a, __int128_t b, __int128_t n)
    {
        a = normalize(a, n);
        __int128_t inv = modinv(b, n);
        return (inv == -1) ? -1 : (a * inv) % n;
    }

    long long part_2(std::string_view path, long long position = 2020, long long size = 119315717514047, long long rounds = 101741582076661) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);

        __int128 A = 0;
        __int128 B = 0;

        for (int i = lines.size() - 1; i >= 0; --i) {
            std::vector<std::string> words = utils::splitString(lines[i], " ");
            long long a = 0, b = 0;
            if (lines[i] == "deal into new stack") {
                a = -1;
                b = size - 1;
            }
            else if (words[0] == "cut") {
                int N = std::stoi(words[1]);
                a = 1;
                b = N;
            }
            else {
                long long int N = std::stoll(words[3]);
                long long inverse = modinv(N, size);
                a = inverse;
                b = 0;
            }
            if (i == lines.size() - 1) {
                A = a;
                B = b;
            }
            else {
                B = a * B + b;
                A = A * a;
            }
            A = normalize(A, size);
            B = normalize(B, size);
        }


        __int128 finalA = 1, finalB = 0;
        __int128 initialA = A;
//        __int128 powerA = 1;
        while (rounds > 0) {
            if (rounds % 2 == 1) {
                finalA *= A;
                finalA = normalize(finalA, size);
            }
            A = A * A;
            A = normalize(A, size);
            rounds = rounds / 2;
        }
        finalB = normalize(B * modular_divide(finalA - 1, initialA - 1, size), size);
        return normalize(finalA * position + finalB, size);
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day22::part_1("../2019/day22/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2019_day22::part_2("../2019/day22/input.in") << std::endl;
//    std::cout << "Part 2: " << aoc2019_day22::part_2("../2019/day22/input.in", 6289, 10007, 1) << std::endl;
//    std::cout << "Part 2: " << aoc2019_day22::part_2("../2019/day22/input_test2.in", 8, 10, 1) << std::endl;
    return 0;
}
#endif
