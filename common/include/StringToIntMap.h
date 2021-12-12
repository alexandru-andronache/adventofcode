#pragma once

#include <map>
#include <string>

/*
 * Assign an index to each string
 */
namespace stringtointmap {
    class StringToIntMap {
    public:
        StringToIntMap();

        void addString(const std::string &str);
        int getIndex(const std::string &str);
        std::string getString(int index);
        int getSize();

    private:
        std::map<std::string, int, std::less<>> mMap;
        std::map<int, std::string, std::less<>> mReverseMap;
        int mIndex{0};
    };
}