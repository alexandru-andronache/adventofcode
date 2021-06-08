#include "VerticalHexGridTest.h"
#include "verticalhexgrid.h"

using namespace verticalhexgrid;

TEST_F(VerticalHexGridTest, test_filling_vertical_hex_grid) {
    const std::vector<std::string> paths{"sesenwnenenewseeswwswswwnenewsewsw",
                                         "neeenesenwnwwswnenewnwwsewnenwseswesw",
                                         "seswneswswsenwwnwse",
                                         "nwnwneseeswswnenewneswwnewseswneseene",
                                         "swweswneswnenwsewnwneneseenw",
                                         "eesenwseswswnenwswnwnwsewwnwsene",
                                         "sewnenenenesenwsewnenwwwse",
                                         "wenwwweseeeweswwwnwwe",
                                         "wsweesenenewnwwnwsenewsenwwsesesenwne",
                                         "neeswseenwwswnwswswnw",
                                         "nenwswwsewswnenenewsenwsenwnesesenew",
                                         "enewnwewneswsewnwswenweswnenwsenwsw",
                                         "sweneswneswneneenwnewenewwneswswnese",
                                         "swwesenesewenwneswnwwneseswwne",
                                         "enesenwswwswneneswsenwnewswseenwsese",
                                         "wnwnesenesenenwwnenwsewesewsesesew",
                                         "nenewswnwewswnenesenwnesewesw",
                                         "eneswnwswnwsenenwnwnwwseeswneewsenese",
                                         "neswnwewnwnwseenwseesewsenwsweewe",
                                         "wseweeenwnesenwwwswnew"};

    const int SIZE = 1000;
    VerticalHexGrid<bool> hexGrid(SIZE, true);

    for (const auto& path : paths) {
        int X = SIZE / 2;
        int Y = SIZE / 2;
        int i = 0;
        while (i < path.size()) {
            int size = 0;
            if (path[i] == 'e' || path[i] == 'w') {
                size = 1;
            }
            else {
                size = 2;
            }
            auto result = hexGrid.moveInHexGridVertical(X, Y, path.substr(i, size));
            X += result.first;
            Y += result.second;
            i += size;
        }
        hexGrid.grid[X][Y] = !hexGrid.grid[X][Y];
    }

    int sol = 0;
    for (const auto& line : hexGrid.grid) {
        sol += std::count(line.begin(), line.end(), false);
    }

    ASSERT_EQ(sol , 10);
}

TEST_F(VerticalHexGridTest, test_neighboors_vertical_hex_grid) {
    const std::vector<std::string> paths{"sesenwnenenewseeswwswswwnenewsewsw",
                                         "neeenesenwnwwswnenewnwwsewnenwseswesw",
                                         "seswneswswsenwwnwse",
                                         "nwnwneseeswswnenewneswwnewseswneseene",
                                         "swweswneswnenwsewnwneneseenw",
                                         "eesenwseswswnenwswnwnwsewwnwsene",
                                         "sewnenenenesenwsewnenwwwse",
                                         "wenwwweseeeweswwwnwwe",
                                         "wsweesenenewnwwnwsenewsenwwsesesenwne",
                                         "neeswseenwwswnwswswnw",
                                         "nenwswwsewswnenenewsenwsenwnesesenew",
                                         "enewnwewneswsewnwswenweswnenwsenwsw",
                                         "sweneswneswneneenwnewenewwneswswnese",
                                         "swwesenesewenwneswnwwneseswwne",
                                         "enesenwswwswneneswsenwnewswseenwsese",
                                         "wnwnesenesenenwwnenwsewesewsesesew",
                                         "nenewswnwewswnenesenwnesewesw",
                                         "eneswnwswnwsenenwnwnwwseeswneewsenese",
                                         "neswnwewnwnwseenwseesewsenwsweewe",
                                         "wseweeenwnesenwwwswnew"};

    const int SIZE = 1000;
    VerticalHexGrid<bool> hexGrid(SIZE, true);

    for (const auto& path : paths) {
        int X = SIZE / 2;
        int Y = SIZE / 2;
        int i = 0;
        while (i < path.size()) {
            int size = 0;
            if (path[i] == 'e' || path[i] == 'w') {
                size = 1;
            }
            else {
                size = 2;
            }
            auto result = hexGrid.moveInHexGridVertical(X, Y, path.substr(i, size));
            X += result.first;
            Y += result.second;
            i += size;
        }
        hexGrid.grid[X][Y] = !hexGrid.grid[X][Y];
    }

    for (int day = 0; day < 3; ++day) {
        std::vector<std::vector<bool>> newGrid = hexGrid.grid;
        hexGrid.calculateNeighbors(false);
        for (int i = 0; i < SIZE; ++i) {
            for (int j = 0; j < SIZE; ++j) {
                if (!hexGrid.grid[i][j]) {
                    if (hexGrid.neighbors[i][j] == 0 || hexGrid.neighbors[i][j] > 2) {
                        newGrid[i][j] = true;
                    }
                    else {
                        newGrid[i][j] = hexGrid.grid[i][j];
                    }
                }
                else {
                    if (hexGrid.neighbors[i][j] == 2) {
                        newGrid[i][j] = false;
                    }
                    else {
                        newGrid[i][j] = hexGrid.grid[i][j];
                    }
                }
            }
        }
        hexGrid.grid = newGrid;
    }

    int sol = 0;
    for (const auto& line : hexGrid.grid) {
        sol += std::count(line.begin(), line.end(), false);
    }

    ASSERT_EQ(sol , 25);
}