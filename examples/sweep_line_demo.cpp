#include <iostream>
#include "../include/geom_algorithms/algorithms/sweep_line.hpp"

using namespace geom;

int main() {
    std::vector<Segment> segments = {
        {{1, 1}, {3, 3}, 1},
        {{2, 2}, {4, 4}, 2},
        {{5, 5}, {7, 7}, 3},
        {{6, 6}, {8, 8}, 4},
        {{1, 3}, {3, 1}, 5},
        {{2, 4}, {4, 2}, 6},
        {{5, 7}, {7, 5}, 7},
        {{6, 8}, {8, 6}, 8}
    };
    findIntersections(segments);
    return 0;
}