#ifndef CONVEX_HULL_HPP
#define CONVEX_HULL_HPP

#include <vector>

struct  Point
{
    int x;
    int y;
};

// Computes the convex hull of a set of points.
// Returns a vector of points representing the convex hull.

std::vector<Point> compute_convex_hull(std::vector<Point> points);

#endif