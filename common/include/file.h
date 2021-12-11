#include <string>

namespace file {
    std::string readFileAsString(std::string_view path);
    std::vector<int> readFileAsArrayInt(std::string_view path);
    std::vector<long long> readFileAsArrayLongLong(std::string_view path, std::string_view separator);
    std::vector<unsigned long long> readFileAsArrayULL(std::string_view path, std::string_view separator);
    std::vector<std::string> readFileAsArrayString(std::string_view path);
    std::vector<std::vector<std::string>> readFileAndSplit(std::string_view path, std::string_view tokens);
    std::vector<std::vector<int>> readFileAsMap(std::string_view path);
}
