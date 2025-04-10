cmake_minimum_required(VERSION 3.15)
project(ComputationalGeometryCpp)

# Suppress policy warnings for Boost
cmake_policy(SET CMP0167 OLD)
cmake_policy(SET CMP0144 OLD)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

# Dependencies
find_package(Boost 1.72 REQUIRED COMPONENTS system filesystem program_options)
find_package(CGAL REQUIRED)

# Create the geometry algorithm library
add_library(geom_algorithms
    src/algorithms/convex_hull.cpp
    src/algorithms/sweep_line.cpp
    src/algorithms/monotone_partition.cpp
    src/algorithms/triangulate_monotone.cpp 
    src/visulization/svg_writer.cpp 
    )

target_include_directories(geom_algorithms
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(geom_algorithms
    PRIVATE
    CGAL::CGAL
    Boost::system
    Boost::filesystem
    Boost::program_options
)

# Demo executable
add_executable(convex_hull_demo
    examples/convex_hull_demo.cpp
)

set_target_properties(convex_hull_demo
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME "convex_hull"
)

# Link demo to library
target_link_libraries(convex_hull_demo
    PRIVATE
    geom_algorithms
)


add_executable(sweep_line_demo
    examples/sweep_line_demo.cpp
)

set_target_properties(sweep_line_demo
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME "sweep_line"
)

target_link_libraries(sweep_line_demo
    PRIVATE
    geom_algorithms
)

add_executable(polygon_triangulation_demo
    examples/polygon_triangulation_demo.cpp
)
set_target_properties(polygon_triangulation_demo
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
    OUTPUT_NAME "polygon_triangulation"
)
target_link_libraries(polygon_triangulation_demo
    PRIVATE
    geom_algorithms
)