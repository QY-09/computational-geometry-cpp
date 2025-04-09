#include "../include/geom_algorithms/algorithms/polygon.hpp"
#include "../include/geom_algorithms/visualization/svg_writer.hpp"
#include "../include/geom_algorithms/algorithms/monotone_partition.hpp"

#include <vector>
#include <iostream>


using namespace geom;

int main() {
    Polygon catface={
        {-1.0, 0.5},
        {-2.0, 2.5},
        {-1.5, 3.0},
        {-2.0, 4.0},
        {-1.0, 3.5},
        {0.0, 3.0},
        {1.0, 3.5},
        {2.0, 4.0},
        {1.5, 3.0},
        {2.0, 2.5},
        {1.0, 0.5},
        {0.0, 1.0}
    };
    
    std::vector<Diagonal> diagonals = compute_monotone_partition(catface);
    // Write SVG to file
    
    for (const auto& d : diagonals) {
        std::cout << "Diagonal: " << d.from << " -> " << d.to << std::endl;
    }
    viz::writeTriangulationSVG("catface.svg", catface, diagonals);


    std::cout << "Cat face polygon triangulation to SVG file completed." << std::endl;

    return 0;

}

