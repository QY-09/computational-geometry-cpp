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

# C++ standard and output name (this is where your error occurred!)
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
