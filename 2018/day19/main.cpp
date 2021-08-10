#include "file.h"
#include "utilities.h"
#include <iostream>
#include <map>
#include <array>

namespace aoc2018_day19 {
    void addr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] + registers[instructions[1]];
    }

    void addi(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] + instructions[1];
    }

    void mulr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] * registers[instructions[1]];
    }

    void muli(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] * instructions[1];
    }

    void banr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] & registers[instructions[1]];
    }

    void bani(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] & instructions[1];
    }

    void borr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] | registers[instructions[1]];
    }

    void bori(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]] | instructions[1];
    }

    void setr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = registers[instructions[0]];
    }

    void seti(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = instructions[0];
    }

    void gtir(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = (instructions[0] > registers[instructions[1]]) ? 1 : 0;
    }

    void gtri(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = (registers[instructions[0]] > instructions[1]) ? 1 : 0;
    }

    void gtrr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = (registers[instructions[0]] > registers[instructions[1]]) ? 1 : 0;
    }

    void eqir(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = (instructions[0] == registers[instructions[1]]) ? 1 : 0;
    }

    void eqri(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = (registers[instructions[0]] == instructions[1]) ? 1 : 0;
    }

    void eqrr(std::array<long long, 6>& registers, const std::array<int, 3>& instructions) {
        registers[instructions[2]] = (registers[instructions[0]] == registers[instructions[1]]) ? 1 : 0;
    }

    int solve(const std::vector<std::pair<std::string, std::array<int, 3>>>& instructions,
              int ip_register,
              std::array<long long, 6> registers = {0, 0, 0, 0, 0, 0}) {
        int ip_value = 0;

        std::map<std::string, void(*)(std::array<long long, 6>&, const std::array<int, 3>&)> func;
        func.insert({"addr", &addr});
        func.insert({"addi", &addi});

        func.insert({"mulr", &mulr});
        func.insert({"muli", &muli});

        func.insert({"banr", &banr});
        func.insert({"bani", &bani});

        func.insert({"borr", &borr});
        func.insert({"bori", &bori});

        func.insert({"setr", &setr});
        func.insert({"seti", &seti});

        func.insert({"gtir", &gtir});
        func.insert({"gtri", &gtri});
        func.insert({"gtrr", &gtrr});

        func.insert({"eqir", &eqir});
        func.insert({"eqri", &eqri});
        func.insert({"eqrr", &eqrr});

        while (ip_value < instructions.size()) {
            registers[ip_register] = ip_value;
            func[instructions[ip_value].first](registers, instructions[ip_value].second);
            ip_value = registers[ip_register];
            ip_value++;
        }

        return registers[0];
    }

    int part_1(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int ip = 0;
        std::vector<std::pair<std::string, std::array<int, 3>>> input;
        for (char i : lines[0]) {
            if (i >= '0' && i <= '9') {
                ip = ip * 10 +  i - '0';
            }
        }
        for (int i = 1; i < lines.size(); ++i) {
            std::vector<std::string> tokens = utils::splitString(lines[i], " ");
            input.push_back({tokens[0], {std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3])}});
        }
        return solve(input, ip);
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        int ip = 0;
        std::vector<std::pair<std::string, std::array<int, 3>>> input;
        for (char i : lines[0]) {
            if (i >= '0' && i <= '9') {
                ip = ip * 10 +  i - '0';
            }
        }
        for (int i = 1; i < lines.size(); ++i) {
            std::vector<std::string> tokens = utils::splitString(lines[i], " ");
            input.push_back({tokens[0], {std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3])}});
        }

        // in part 2 it will generate a big number in the third position in the register
        // and then it will add in the register[0] the sum of all divisors of register[3]
        // it will do this by trying to multiplicate all the numbers between 1 and register[3] and compare the result with register[3]
        // To speed up the calculations I cut the instructions after the register[3] was generated and the manually calculate the sum

        std::array<long long, 6> registers = {1, 0, 0, 0, 0, 0};
        int ip_value = 0;

        std::map<std::string, void(*)(std::array<long long, 6>&, const std::array<int, 3>&)> func;
        func.insert({"addr", &addr});
        func.insert({"addi", &addi});

        func.insert({"mulr", &mulr});
        func.insert({"muli", &muli});

        func.insert({"banr", &banr});
        func.insert({"bani", &bani});

        func.insert({"borr", &borr});
        func.insert({"bori", &bori});

        func.insert({"setr", &setr});
        func.insert({"seti", &seti});

        func.insert({"gtir", &gtir});
        func.insert({"gtri", &gtri});
        func.insert({"gtrr", &gtrr});

        func.insert({"eqir", &eqir});
        func.insert({"eqri", &eqri});
        func.insert({"eqrr", &eqrr});

        while (registers[3] < 1000000) {
            registers[ip] = ip_value;
            func[input[ip_value].first](registers, input[ip_value].second);
            ip_value = registers[ip];
            ip_value++;
        }

        int n = registers[3];
        int sum = 0;
        for (int i = 1; i <= n; ++i) {
            if (n % i == 0) {
                sum += i;
            }
        }
        return sum;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2018_day19::part_1("../2018/day19/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2018_day19::part_2("../2018/day19/input.in") << std::endl;

    return 0;
}
#endif
