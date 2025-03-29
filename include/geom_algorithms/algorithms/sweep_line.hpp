#pragma once
#include <vector>

namespace geom{
    struct Point
    {
        int x;
        int y;
    };

    struct Segment
    {
        Point p, q;
        int id;
    };

    // public call function:
    void findIntersections(const std::vector<Segment>& segments);
}