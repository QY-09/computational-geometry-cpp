#include "../include/geom_algorithms/visualization/svg_writer.hpp"
#include "../include/geom_algorithms/algorithms/polygon.hpp"
#include "../include/geom_algorithms/algorithms/monotone_partition.hpp"
#include <fstream> 
#include <stdexcept> 

namespace geom::viz {

    namespace {
        // Utility for coordinate transform: scale and center on canvas
        constexpr int width = 800;
        constexpr int height = 800;
        constexpr double scale = 100.0;
        constexpr double offset_x = width / 2.0;
        constexpr double offset_y = height / 2.0;
    
        double svgX(double x) { return x * scale + offset_x; }
        double svgY(double y) { return height - (y * scale + offset_y); }
    }
    
    void writePolygonSVG(const std::string& filename, const Polygon& poly) {
        std::ofstream out(filename);
        if (!out) throw std::runtime_error("Failed to open file: " + filename);
    
        out << "<svg xmlns='http://www.w3.org/2000/svg' width='" << width
            << "' height='" << height << "' viewBox='0 0 " << width << " " << height << "'>\n";
    
        out << "<polygon points='";
        for (const auto& p : poly) {
            out << svgX(p.x) << "," << svgY(p.y) << " ";
        }
        out << "' style='fill:none;stroke:black;stroke-width:2'/>\n";
        out << "</svg>\n";
    }
    
    void writeTriangulationSVG(const std::string& filename, const Polygon& poly, const std::vector<Diagonal>& diagonals) {
        std::ofstream out(filename);
        if (!out) throw std::runtime_error("Failed to open file: " + filename);
    
        out << "<svg xmlns='http://www.w3.org/2000/svg' width='" << width
            << "' height='" << height << "' viewBox='0 0 " << width << " " << height << "'>\n";
    
        // Outer polygon
        out << "<polygon points='";
        for (const auto& p : poly) {
            out << svgX(p.x) << "," << svgY(p.y) << " ";
        }
        out << "' style='fill:none;stroke:black;stroke-width:2'/>\n";
    
        // Diagonals
        for (const auto& d : diagonals) {
            const Point& p = poly[d.from];
            const Point& q = poly[d.to];
    
            out << "<line x1='" << svgX(p.x) << "' y1='" << svgY(p.y)
                << "' x2='" << svgX(q.x) << "' y2='" << svgY(q.y)
                << "' stroke='red' stroke-width='1' stroke-dasharray='4 2'/>\n";
        }
    
    
        out << "</svg>\n";
    }
    
    } // namespace geom::viz
