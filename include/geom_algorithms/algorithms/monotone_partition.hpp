#pragma once

#include <vector>
#include "../include/geom_algorithms/algorithms/polygon.hpp"

namespace geom{
//  type of the vertex

enum class VertexType {
    START,
    END,SPLIT,MERGE,REGULAR
};
// diagonal to insert
struct Diagonal{
    int from;
    int to; 

};
// input polygon return a list of diagonal to make y-monotone
std::vector<Diagonal>compute_monotone_partition(const Polygon& poly);

}
