#include "../include/geom_algorithms/algorithms/monotone_partition.hpp"
#include <map>
#include <algorithm>
#include <cmath>
#include <iostream>

namespace geom{

    static double sweep_y = 0.0;
    // compute orientation of the edge
    static int orientation(const Point& p, const Point& q, const Point& r) {
        double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (std::abs(val) <= 1e-9) return 0; // collinear
        return (val > 0) ? 1 : 2; // clock or counterclock wise
    }
    // compare the y coordinate of the point with the sweep line
    static bool above(const Point&p, const Point& q){
        return (p.y> q.y) || (p.y == q.y && p.x< q.x);  
    }


// identify the type of the vertex

static VertexType vertex_type(const Polygon& poly, int idx){
    int n = poly.size();
    const Point& prev = poly[(idx - 1 + n) % n]; // previous vertex, i start from 0
    const Point& curr = poly[idx];
    const Point& next = poly[(idx + 1) % n];

    if(above(prev,curr) && above(next,curr)){
        return orientation(prev, curr, next) == 2 ? VertexType::START : VertexType::SPLIT;
    } else if(above(curr,prev) && above(curr,next)){
        return orientation(prev, curr, next) == 2 ? VertexType::END : VertexType::MERGE;
    } else{
        return VertexType::REGULAR;
    }
}

// sweep line algorithm to compute the y-monotone partition

struct SweepEdge{
    int start, end;
    SweepEdge(int a, int b){
        start = std::min(a,b);
        end = std::max(a,b);
    }

    bool operator==(const SweepEdge& other) const {
        return start == other.start && end == other.end;
    }
};

// comparator for the sweep line:   which edge is directly to the left of the current vertex?
struct SweepEdgeComparator{
    const Polygon& poly;
    SweepEdgeComparator(const Polygon& p) : poly(p) {}
    double getXAtY(const Point& p, const Point& q, double y) const {
        if (std::abs(p.y -q.y)<1e-9) return p.x; // horizontal edge
        return p.x + (q.x - p.x) * (y - p.y) / (q.y - p.y);
    }
    bool operator()(const SweepEdge& a, const SweepEdge& b) const {
        double x1 = getXAtY(poly[a.start], poly[a.end], sweep_y);
        double x2 = getXAtY(poly[b.start], poly[b.end], sweep_y);
        if (std::abs(x1 - x2) < 1e-9) 
            return a.start < b.start; // tie-breaker
        return x1 < x2;
        }
    };

// main function: compute the y-monotone partition of the polygon
std::vector<Diagonal> compute_monotone_partition(const Polygon& poly){
    int n = poly.size();
    std::vector<Diagonal> diagonals;

    //sorting verticed by y coordinats(top to bottom)
    std::vector<int> sorted_indices(n);
    for (int i=0; i<n; i++){sorted_indices[i] = i;} 
    std::sort(sorted_indices.begin(), sorted_indices.end(), [&](int a, int b){
        const Point& p1 = poly[a];
        const Point& p2 = poly[b];
        return p1.y> p2.y || (p1.y == p2.y && p1.x < p2.x);
    });
    //classify the vertex type
    std::vector<VertexType> vtypes(n);
    for (int i=0;i<n;i++)
        vtypes[i]=vertex_type(poly, i);

    //sweep status structure
    
    auto comp= SweepEdgeComparator(poly);
    std::map<SweepEdge, int, SweepEdgeComparator> status(comp);

    //sweep throungh sorted vertices
    for (int vi: sorted_indices){
        const Point& curr = poly[vi];
        sweep_y = curr.y; // update the sweep line

        VertexType vtype = vtypes[vi];
        int prev = (vi - 1 + n) % n;
        int next = (vi + 1) % n;


        // handle the vertex type
        switch (vtype){
            case VertexType::START:
                {
                    // add the edge to the sweep status
                    SweepEdge e(vi, next);
                    status[e] = vi;
                    break;
                }
             
            case VertexType::END:
                {
                    // remove the edge from the sweep status
                    SweepEdge e(prev, vi);
                    if (vtypes[status[e]]==VertexType::MERGE)
                        diagonals.push_back({vi, status[e]});
                    status.erase(e);
                    break;
                }
            case VertexType::SPLIT:
                {
                    // split the edge and add a diagonal
                    auto lower = status.lower_bound(SweepEdge(vi, vi));
                    if (lower != status.begin()) --lower;
                    int helper = lower->second;
                    diagonals.push_back({vi, helper});
                    lower->second = vi;
                    // add the new edge to the sweep status
                    SweepEdge e(vi, next);
                    status[e] = vi;
                    break;
                }
            case VertexType::MERGE:
                {
                    // merge the edges and add a diagonal
                    SweepEdge e(prev, vi);
                    auto it = status.find(e);
        
                    if (it != status.end()) {
                        int helperindx = it->second;
                        if (vtypes[helperindx] == VertexType::MERGE)
                            diagonals.push_back({vi, helperindx});
                        status.erase(it);
                    }
                
                    auto lower = status.lower_bound(SweepEdge(vi, vi));
                    if (lower != status.begin()) --lower;
                    int helper = lower->second;
                    if (vtypes[helper] == VertexType::MERGE)
                        diagonals.push_back({vi, helper});
                    lower->second = vi;
                }
            case VertexType::REGULAR:
            {
                const Point& prev_pt = poly[prev];
                if (curr.y < prev_pt.y) { // right chain
                    SweepEdge e(prev, vi);
                    if (vtypes[status[e]] == VertexType::MERGE)
                        diagonals.push_back({vi, status[e]});
                    status.erase(e);
            
                    SweepEdge e_new(vi, next);
                    status[e_new] = vi;
                } else { // left chain
                    auto it = status.lower_bound(SweepEdge(vi, vi));
                    if (it != status.begin()) --it;
                    if (vtypes[it->second] == VertexType::MERGE)
                        diagonals.push_back({vi, it->second});
                    it->second = vi;
                }
                break;   
            }
                
        }
    }

    return diagonals;
}
}
