#include "../include/geom_algorithms/algorithms/convex_hull.hpp"
#include <algorithm> // for std::sort
#include <vector> 

// function for calculating cross production of two vectors

int cross_product(const Point& p0, const Point& p1, const Point& p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p1.y - p0.y) * (p2.x - p0.x);
}

std::vector<Point> compute_convex_hull(std::vector<Point> points) {
    // check if the points number is less than 3
    if (points.size() <= 3) {
        return points; // Convex hull is not possible
    }
    // Sort the points lexicographically
    std::sort(points.begin(),points.end(), [](const Point& a, const Point& b) {
        return (a.x < b.x) || (a.x == b.x && a.y < b.y);
    });

    // create a vector to store the convex hull; the size ths 2* points.size()
    std::vector<Point> H(2 * points.size());
    int k = 0;
    // Build the lower hull
    for (int i =0; i< points.size(); ++i){
        while (k >=2 && cross_product(H[k-2],H[k-1], points[i])<=0)
            k--;
        H[k++] = points[i];
    }
    // Build the upper hull
    for (int i = points.size() - 1, t = k + 1; i >= 0; --i) {
        while (k >= t && cross_product(H[k-2], H[k-1], points[i]) <= 0)
            k--;
        H[k++] = points[i];
    }
    H.resize(k-1);
    return H;
}

