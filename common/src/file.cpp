#include "file.h"
#include "utilities.h"
#include <fstream>
#include <vector>
#include <string>
#include <iterator>

namespace file {

    std::string readFileAsString(std::string_view path) {
        constexpr auto read_size = std::size_t{4096};
        auto stream = std::ifstream{path.data()};
        stream.exceptions(std::ios_base::badbit);

        auto out = std::string{};
        auto buf = std::string(read_size, '\0');
        while (stream.read(& buf[0], read_size)) {
            out.append(buf, 0, stream.gcount());
        }
        out.append(buf, 0, stream.gcount());
        return out;
    }

    std::vector<int> readFileAsArrayInt(std::string_view path) {
        std::ifstream f(path.data());
        std::istream_iterator<int> start(f), end;
        return std::vector<int>(start, end);
    }

    std::vector<long long> readFileAsArrayLongLong(std::string_view path, std::string_view separator) {
        std::string str = readFileAsString(path);
        std::vector<std::string> numbers = utils::splitString(str, separator);
        std::vector<long long> result;
        for (const auto& nr : numbers) {
            result.push_back(std::stoll(nr));
        }
        return result;
    }

    std::vector<unsigned long long> readFileAsArrayULL(std::string_view path, std::string_view separator) {
        std::string str = readFileAsString(path);
        std::vector<std::string> numbers = utils::splitString(str, separator);
        std::vector<unsigned long long> result;
        for (const auto& nr : numbers) {
            result.push_back(std::stoull(nr));
        }
        return result;
    }

    std::vector<std::string> readFileAsArrayString(std::string_view path) {
        std::ifstream f(path.data());
        std::string line;
        std::vector<std::string> output;
        while (std::getline(f, line)) {
            output.emplace_back(line);
        }
        f.close();
        return output;
    }

    std::vector<std::vector<std::string>> readFileAndSplit(std::string_view path, std::string_view tokens) {
        std::ifstream f(path.data());
        std::string line;
        std::vector<std::vector<std::string>> output;
        while (std::getline(f, line)) {
            output.emplace_back(utils::splitString(line, tokens));
        }
        f.close();
        return output;
    }

    std::vector<std::vector<int>> readFileAsMap(std::string_view path) {
        std::vector<std::string> lines = file::readFileAsArrayString(path);
        std::vector<std::vector<int>> output;
        for (const auto& line : lines) {
            std::vector<int> numbers;
            for (const auto& c : line) {
                numbers.push_back(c - '0');
            }
            output.push_back(numbers);
        }
        return output;
    }

    std::vector<std::vector<int>> readFileAsVectorOfVectors(std::string_view path) {
        std::string str = file::readFileAsString(path);
        std::vector<std::string> lines = utils::splitString(str, "\n");
        std::vector<std::vector<std::string>> map;
        map.reserve(lines.size());
        for (const auto& line : lines) {
            map.emplace_back(utils::splitString(line, " "));
        }
        std::vector<std::vector<int>> input;
        for (auto & line : map) {
            std::vector<int> temp;
            temp.reserve(line.size());
            for (const auto & nr : line) {
                temp.emplace_back(std::stoi(nr));
            }
            input.emplace_back(temp);
        }

        return input;
    }
}