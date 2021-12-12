#include <string>

namespace string {
    /*
     * return the number of substrings s in str
     */
    int findNumberOfSubstrings(std::string_view str, std::string_view s);

    /*
     * returns true if all letters are upper case in the string
     */
    bool isUpperCaseString(std::string_view str);
}
