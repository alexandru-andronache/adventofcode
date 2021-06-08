#include "string_util.h"

namespace string {
    int findNumberOfSubstrings(std::string_view str, std::string_view s) {
        int nr = 0;
        for (int i = 0; i <= str.size() - s.size(); ++i) {
            nr += (str.substr(i, s.size()) == s);
        }
        return nr;
    }
}