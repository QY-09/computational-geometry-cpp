#include "../include/geom_algorithms/algorithms/sweep_line.hpp"
#include <iostream>
#include <queue>
#include <cmath>

namespace geom{
    const double EPS = 1e-9;
    // Helper functions including: orientation, onSegment, doIntersect, and findIntersection
    int orientation(const Point& p, const Point& q, const Point& r){
        double val =  (q.x - p.x) * (r.y - q.y)-(q.y - p.y) * (r.x - q.x);
        if (std::abs(val) < EPS) return 0; // val> 0 left turn counter clockwise, val < 0 right turn clockwise
        return (val < 0) ? 1 : 2; // 1 for clockwise, 2 for counter clockwise
    }

    //check if point q is on segment pr
    bool onSegment(const Point& p, const Point& q, const Point& r){
        if (q.x <= std::max(p.x, r.x)+EPS && q.x >= std::min(p.x, r.x)-EPS &&
            q.y <= std::max(p.y, r.y)+EPS && q.y >= std::min(p.y, r.y)-EPS)
            return true;
        return false;
    }


    //check if segments p1q1 and p2q2 intersect
    bool lineIntersect( const Segment& s1, const Segment& s2, Point& pt_intersec_){
        Point p1 = s1.p, q1 = s1.q;
        Point p2 = s2.p, q2 = s2.q;
        int o1 = orientation(p1, q1, p2); // orientation of p2 with respect to p1q1
        int o2 = orientation(p1, q1, q2); // orientation of q2 with respect to p1q1
        int o3 = orientation(p2, q2, p1); // orientation of p1 with respect to p2q2
        int o4 = orientation(p2, q2, q1); // orientation of q1 with respect to p2q2
        // if the intersect point is any of the end points of the segments
        if (o1==0 && onSegment(p1, p2, q1)){
            pt_intersec_ = p2;
            return true;
        }
        if (o2==0 && onSegment(p1, q2, q1)){
            pt_intersec_ = q2;
            return true;
        }
        if (o3==0 && onSegment(p2, p1, q2)){
            pt_intersec_ = p1;
            return true;
        }
        if (o4==0 && onSegment(p2, q1, q2)){
            pt_intersec_ = q1;
            return true;
        }
        // General case
        if (o1!=o2 && o3!=o4) {
            double a1= q1.y - p1.y;
            double b1= p1.x - q1.x;
            double c1= a1*p1.x + b1*p1.y;

            double a2= q2.y - p2.y;
            double b2= p2.x - q2.x;
            double c2= a2*p2.x + b2*p2.y;

            double det = a1*b2 - a2*b1;
            if (std::fabs(det)<EPS) return false;

            pt_intersec_.x = (b2*c1 - b1*c2)/det;
            pt_intersec_.y = (a1*c2 - a2*c1)/det;

            return true;}
        
        return false;
        
    }
    

    void findIntersections(const std::vector<Segment>& segments){
        struct Event{
            double x;   // x-coordinate of the event
            Segment segment; // segment associated with the event
            bool isStart; // true if the start of the segment, false if the end of the segment
            
            bool operator<(const Event& other) const {
                return x> other.x; // min-heap 
            }
        };

        std::priority_queue<Event> eventQueue;
        
        //1. Push segment start and end points into the event queue
        for (const auto& s:segments){
            Segment ordered=s;
            if (s.q.x< s.p.x) std::swap(ordered.p, ordered.q);
            eventQueue.push({static_cast<double>(ordered.p.x),ordered, true}); //start
            eventQueue.push({static_cast<double>(ordered.q.x),ordered,false}); //end
        }
        
        std::vector<Segment> activeSegments;
        //2. process events
        while (!eventQueue.empty()){
            Event event = eventQueue.top();
            eventQueue.pop();

            Segment currentSegment = event.segment;
            Point pt_intersec_;

            if (event.isStart) {
                //3. check for intersections with active segments
                for (const auto& s:activeSegments){
                    
                    if (lineIntersect(currentSegment, s, pt_intersec_)){
                        std::cout << "Intersection between segment " << currentSegment.id << " and segment " << s.id << " at point (" << pt_intersec_.x << ", " << pt_intersec_.y << ")" << std::endl;
                    }
                }
                activeSegments.push_back(currentSegment);
            } else {
                //4. remove the segment from the active list
                activeSegments.erase(std::remove_if(
                    activeSegments.begin(),
                    activeSegments.end(),
                    [&](const Segment& s) {
                        return s.id == currentSegment.id;
                    }),
                    activeSegments.end());
                
            }
        }


    }
}