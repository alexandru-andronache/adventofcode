#include "file.h"
#include "utilities.h"
#include <iostream>
#include <cmath>
#include <optional>
#include <queue>
#include <numeric>

#ifdef TESTING
#include <gtest/gtest.h>
#endif

namespace aoc2023_day20 {
    enum type {
        None,
        Flip,
        Conjunction,
        Broadcast,
    };
    enum frequency {
        low,
        high
    };
    struct message {
        std::string start;
        std::string end;
        bool val;
    };
    struct Module
    {
        std::string name;
        type type = type::None;
        bool state = false;
        std::map<std::string, bool> inputs;
        std::vector<std::string> output;
    };

    void send(Module& mod, std::queue<message> &messages, std::string inputName, bool pulse) {
        switch (mod.type) {
            case type::Broadcast:
                for (const auto& module : mod.output) {
                    messages.push({ mod.name, module, pulse });
                }
                break;
            case type::Flip:
                if (!pulse) {
                    mod.state = !mod.state;
                    for (const auto& module : mod.output) {
                        messages.push({ mod.name, module, mod.state });
                    }
                }
                break;
            case type::Conjunction:
                mod.inputs[inputName] = pulse;
                mod.state = false;
                for (const auto& input : mod.inputs) {
                    if (!input.second) {
                        mod.state = true;
                        break;
                    }
                }
                for (const auto& module : mod.output) {
                    messages.push({ mod.name, module, mod.state });
                }
                break;
            case type::None:
                break;
        }
    }

    unsigned long long part_1(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::map<std::string, Module> modules;
        for (const auto& line : input) {
            std::vector<std::string> tokens = utils::splitString(line, " ,->");
            Module m;
            if (tokens[0].starts_with('&')) {
                m.name = tokens[0].substr(1);
                m.type = type::Conjunction;
            }
            else if (tokens[0].starts_with('%')) {
                m.name = tokens[0].substr(1);
                m.type = type::Flip;
            }
            else {
                m.type = type::Broadcast;
                m.name = tokens[0];
            }
            for (int i = 1; i < tokens.size(); ++i) {
                m.output.push_back(tokens[i]);
            }
            modules[m.name] = m;
        }

        for (const auto& module : modules) {
            for (const auto& out : module.second.output) {
                modules[out].inputs[module.first] = false;
            }
        }

        std::queue<message> messages;
        unsigned long long high = 0;
        unsigned long long low = 0;
        for (int i = 0; i < 1000; i++) {
            messages.push({ "button", "broadcaster", false });
            while (!messages.empty()) {
                auto message = messages.front();
                messages.pop();
                if (message.val) {
                    high++;
                }
                else {
                    low++;
                }
                send(modules[message.end], messages, message.start, message.val);
            }
        }

        return high * low;
    }

    unsigned long long part_2(std::string_view path) {
        std::vector<std::string> input = file::readFileAsArrayString(path);

        std::map<std::string, Module> modules;
        for (const auto& line : input) {
            std::vector<std::string> tokens = utils::splitString(line, " ,->");
            Module m;
            if (tokens[0].starts_with('&')) {
                m.name = tokens[0].substr(1);
                m.type = type::Conjunction;
            }
            else if (tokens[0].starts_with('%')) {
                m.name = tokens[0].substr(1);
                m.type = type::Flip;
            }
            else {
                m.type = type::Broadcast;
                m.name = tokens[0];
            }
            for (int i = 1; i < tokens.size(); ++i) {
                m.output.push_back(tokens[i]);
            }
            modules[m.name] = m;
        }

        for (const auto& module : modules) {
            for (const auto& out : module.second.output) {
                modules[out].inputs[module.first] = false;
            }
        }

        std::queue<message> messages;
        std::string destRx = modules["rx"].inputs.begin()->first;

        std::map<std::string, unsigned long long> previous;
        std::map<std::string, unsigned long long> loops;
        std::vector<unsigned long long> lengths;
        unsigned long long index = 1;
        bool done = false;
        while (!done) {
            messages.push({ "button", "broadcaster", false });
            while (!messages.empty() && !done) {
                auto message = messages.front();
                messages.pop();
                send(modules[message.end], messages, message.start, message.val);
                if (message.end == destRx && message.val) {
                    if (!loops.contains(message.start)) {
                        if (previous.contains(message.start)) {
                            loops[message.start] = index - previous[message.start];
                            lengths.push_back(loops[message.start]);
                            if (lengths.size() == modules[modules["rx"].inputs.begin()->first].inputs.size()) {
                                done = true;
                            }
                        }
                        else
                        {
                            previous[message.start] = index;
                        }
                    }
                }
            }
            index++;
        }

        unsigned long long lcm = lengths[0];
        for (int i = 1; i < lengths.size(); ++i) {
            lcm = std::lcm(lcm, lengths[i]);
        }
        return lcm;

    }
}

#ifdef TESTING
TEST(Tests2023Day20, part_1_test) {
    ASSERT_EQ(aoc2023_day20::part_1("../2023/day20/input_test.in"), 32000000);
}

TEST(Tests2023Day20, part_1_real_test) {
    ASSERT_EQ(aoc2023_day20::part_1("../2023/day20/input.in"), 832957356);
}

TEST(Tests2023Day20, part_2_real_test) {
    ASSERT_EQ(aoc2023_day20::part_2("../2023/day20/input.in"), 240162699605221);
}
#endif


#ifndef TESTING
int main() {
    std::cout << "Part 1: " << aoc2023_day20::part_1("../2023/day20/input.in") << std::endl;
    std::cout << "Part 2: " << aoc2023_day20::part_2("../2023/day20/input.in") << std::endl;

    return 0;
}
#endif
