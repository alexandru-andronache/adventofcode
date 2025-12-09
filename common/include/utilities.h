#pragma once

#include <string>
#include <vector>

namespace utils {
    template <typename T>
    struct pointT {
        T x;
        T y;
        constexpr pointT() = default;
        constexpr pointT(T _x, T _y) : x(_x), y(_y) {}
        constexpr pointT(pointT&&) = default;
        constexpr pointT(const pointT&) = default;
        pointT& operator=(const pointT&) = default;
        pointT& operator=(pointT&&) = default;

        auto operator<=>(const pointT&) const = default;

        T distanceX(const pointT& other) const {
            return other.x >= x ? other.x - x + 1 : x - other.x + 1;
        }
        T distanceY(const pointT& other) const {
            return other.y >= y ? other.y - y + 1 : y - other.y + 1;
        }
    };

    template <typename T>
    class edge{
    public:
        utils::pointT<T> u;
        utils::pointT<T> v;
        constexpr edge() = default;
        constexpr edge(utils::pointT<T> _x, utils::pointT<T> _y) : u(_x), v(_y) {}

        constexpr edge(edge&&) = default;
        constexpr edge(const edge&) = default;
        edge& operator=(const edge&) = default;
        edge& operator=(edge&&) = default;

        auto operator<=>(const edge&) const = default;
        [[nodiscard]] bool vertical() const {
            return u.x == v.x;
        }
        [[nodiscard]] bool horizontal() const {
            return u.y == v.y;
        }
    };


    struct point {
        int x;
        int y;
        constexpr point()=default;
        constexpr point(int _x, int _y) : x(_x), y(_y) {}
        constexpr point(point&&) = default;
        constexpr point(const point&) = default;
        point& operator=(const point&) = default;
        point& operator=(point&&) = default;

        auto operator<=>(const point&) const = default;
    };

    struct point3d {
        int x;
        int y;
        int z;
    };

    bool isInteger(std::string_view str);
    int getNumber(std::string_view str, int& pos);
    int getNumberWithoutUpdate(std::string_view str, int pos);
    std::vector<std::string> splitString(std::string_view str, std::string_view delimeters);
    std::vector<int> splitStringToInt(std::string_view str, std::string_view delimeters);
    std::vector<long long> splitStringToLL(std::string_view str, std::string_view delimeters);
    std::vector<unsigned long long> splitStringToULL(std::string_view str, std::string_view delimeters);
    unsigned long long decimalToInt(std::string_view str, char character = '1');
    int decimalToInt(const std::vector<bool>& str, bool defaultValue = true);
    int manhattanDistance(int x1, int y1, int x2, int y2);
    bool isAnagram(std::string_view s1, std::string_view s2);
    std::vector<point> getListOfNeighbours4Directions(int x, int y, const std::vector<std::vector<int>>& map);
    std::vector<point> getListOfNeighboursAllDirections(int x, int y, const std::vector<std::vector<int>>& map);
    std::vector<point> getListOfNeighboursAllDirections(int x, int y, int sizeX, int sizeY);
    std::vector<point> getListOfNeighbours4Directions2(int x, int y, int sizeX, int sizeY);

    std::pair<int, int> findValue(const std::vector<std::string>& map, char value);
    point findValue(const std::vector<std::vector<char>>& map, char value);
    std::vector<point> findAll(const std::vector<std::string>& map, char value);

    template<typename T>
    std::string vectorToString(const std::vector<T>& vec, char delimiter) {
        if (vec.empty()) {
            return "";
        }
        std::string output = std::to_string(vec[0]);
        for (int i = 1; i < vec.size(); ++i) {
            output += delimiter + std::to_string(vec[i]);
        }
        return output;
    }
}
