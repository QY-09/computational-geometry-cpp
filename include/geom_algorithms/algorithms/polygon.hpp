#pragma once
#include <vector>

namespace geom{
    struct Point
    {
        double x;
        double y;
    };
    struct Edge{
        Point p, q;  // p start point, q end point
    };

    using Polygon = std::vector<Point>;
}

