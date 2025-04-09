#pragma once
#include <string>
#include <vector>
#include "../include/geom_algorithms/algorithms/polygon.hpp"
#include "../include/geom_algorithms/algorithms/monotone_partition.hpp"

namespace geom::viz{

    void writePolygonSVG(const std::string& filename, const Polygon& poly);
    void writeTriangulationSVG(const std::string& filename, const Polygon& poly, const std::vector<Diagonal>& diagonals);
}

