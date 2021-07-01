#include "file.h"
#include "intcode.h"
#include <iostream>

namespace aoc2019_day25 {
    int part_1(std::string_view path) {
        std::vector<unsigned long long> input = file::readFileAsArrayULL(path, ",");
        std::vector<std::string> commands = {"east\n",
                                             "take antenna\n",
                                             "west\n",
                                             "north\n",
                                             "take weather machine\n",
                                             "north\n",
                                             "east\n",
                                             "take spool of cat6\n",
                                             "east\n",
                                             "north\n",
                                             "west\n",
                                             "north\n",
                                             "south\n",
                                             "east\n",
                                             "east\n",
                                             "north\n",
                                             "north\n",
                                             "south\n",
                                             "south\n",
                                             "south\n",
                                             "east\n",
                                             "south\n",
                                             "north\n",
                                             "west\n",
                                             "north\n",
                                             "west\n",
                                             "south\n",
                                             "south\n",
                                             "take mug\n",
                                             "north\n",
                                             "west\n",
                                             "south\n",
                                             "south\n",
                                             "east\n"};

        intcode::IntCode<unsigned long long> droid(input, {});
        auto exit = droid.advance();
        while ((char)exit.returnValue != '?') {
            exit = droid.advance();
        }
        exit = droid.advance();

        for (const auto& command : commands) {
            for (const auto& c : command) {
                droid.inputIDs.push_back(c);
            }
            std::string output;
            for (int i = 0; i < 200; ++i) {
                exit = droid.advance();
                output += (char)exit.returnValue;
            }
            if (output.find("Analysis complete! You may proceed.") != std::string::npos) {
                std::string newOutput;
                for (int i = 0; i < 200; ++i) {
                    exit = droid.advance();
                    newOutput += (char)exit.returnValue;
                }
                std::string stringBeforeResult = "typing ";
                auto pos = newOutput.find(stringBeforeResult);
                auto numberEnd = newOutput.find(' ', pos + stringBeforeResult.size());
                return std::stoi(newOutput.substr(pos + stringBeforeResult.size(), numberEnd - stringBeforeResult.size() - pos));
            }
        }

        return 0;
    }
}

#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2019_day25::part_1("../2019/day25/input.in") << std::endl;
    return 0;
}
#endif
