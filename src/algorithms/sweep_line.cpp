#include "../include/geom_algorithms/algorithms/sweep_line.hpp"
#include <iostream>
#include <queue>
#include <cmath>

namespace geom{
    const double EPS = 1e-9;
    // Helper functions including: orientation, onSegment, doIntersect, and findIntersection
    int orientation(const Point& p, const Point& q, const Point& r){
        double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (std::abs(val) < EPS) return 0;
        return (val > 0) ? 1 : 2;
    }

    //check if point q is on segment pr
    bool onSegment(

    )

    //check if segments p1q1 and p2q2 intersect
    bool lineIntersect(

    )

    void findIntersections(const std::vector<Segment>& segments){
        struct Event{
            double x;
            Segment segment;
            
        }

    }
}