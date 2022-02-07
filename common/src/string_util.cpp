#include "string_util.h"
#include <algorithm>

namespace string {
    int findNumberOfSubstrings(std::string_view str, std::string_view s) {
        int nr = 0;
        for (int i = 0; i <= str.size() - s.size(); ++i) {
            nr += (str.substr(i, s.size()) == s);
        }
        return nr;
    }
    bool isUpperCaseString(std::string_view str) {
        return std::all_of(str.begin(), str.end(), [](const auto& c) {
            return (c >= 'A' && c <= 'Z');
        });
//        for (const auto& c : str) {
//            if (c >= 'a' && c <= 'z') {
//                return false;
//            }
//        }
//        return true;
    }
}