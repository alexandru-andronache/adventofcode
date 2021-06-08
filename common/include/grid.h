#include <string>
#include <vector>

namespace grid {
    template <class T>
    int numberOfNeighbors(const std::vector<std::vector<T>>& grid, int x, int y, T value) {
        int neighbors = (x > 0 && y > 0 && grid[x - 1][y - 1] == value);
        neighbors += (x > 0 && grid[x - 1][y] == value);
        neighbors += (x > 0 && y + 1 < grid[0].size() && grid[x - 1][y + 1] == value);
        neighbors += (y > 0 && grid[x][y - 1] == value);
        neighbors += (y + 1 < grid[0].size() && grid[x][y + 1] == value);
        neighbors += (x + 1 < grid.size() && y > 0 && grid[x + 1][y - 1] == value);
        neighbors += (x + 1 < grid.size() && grid[x + 1][y] == value);
        neighbors += (x + 1 < grid.size() && y + 1 < grid[0].size() && grid[x + 1][y + 1] == value);
        return neighbors;
    }
}
