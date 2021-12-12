#include <StringToIntMap.h>

using namespace stringtointmap;

StringToIntMap::StringToIntMap() {

}

void StringToIntMap::addString(const std::string& str) {
    if (mMap.find(str) == mMap.end()) {
        mMap.insert({str, mIndex});
        mReverseMap.insert({mIndex, str});
        mIndex++;
    }
}

int StringToIntMap::getIndex(const std::string& str) {
    if (mMap.find(str) == mMap.end()) {
        return -1;
    }
    return mMap[str];
}

std::string StringToIntMap::getString(int index) {
    if (mReverseMap.find(index) == mReverseMap.end()) {
        return "";
    }
    return mReverseMap[index];
}
