#include <iostream>
#include <vector>
#include "../include/geom_algorithms/algorithms/convex_hull.hpp"

int main() {
    std::vector<Point> points ={
        {0, 3}, {2, 2}, {1, 1}, {2, 1},
        {3, 0}, {0, 0}, {3, 3}
    };
    std::vector<Point> hull= compute_convex_hull(points);
    std::cout << "Convex Hull points: " << std::endl;
    for (const auto&p : hull){
        std::cout<< "("<<p.x<<","<<p.y<<")"<<std::endl;
        }
    return 0;
}