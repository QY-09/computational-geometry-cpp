#pragma once
#include <string>
#include <vector>
#include "../geom_algorithms/algorithms/polygon.hpp"

namespace geo::viz{

    void writePolygonSVG(const std::string& filename, const Polygon& poly);
    void writeTriangulationSVG(const std::string& filename, const Polygon& poly, const std::vector<Edge>& diagonals);
}

