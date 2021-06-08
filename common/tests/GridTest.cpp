#include "GridTest.h"
#include "grid.h"

using namespace grid;

TEST_F(Grid, calculate_neighbors)
{
    ASSERT_EQ(numberOfNeighbors({{false, false, false},
                                 {true, true, false},
                                 {false, true, true}}, 1, 1, true), 3);
}

TEST_F(Grid, calculate_neighbors_edge)
{
    ASSERT_EQ(numberOfNeighbors({{false, false, false},
                                 {true, true, false},
                                 {false, true, true}}, 0, 0, true), 2);
}