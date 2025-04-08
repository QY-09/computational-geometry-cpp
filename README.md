# computational-geometry-cpp
Computational geometry algorithms in C++ featuring CGAL integration and topology optimization
## Project Structure
```
computational-geometry-cpp/
├── CMakeLists.txt
├── build/
├── include/
│   ├── core/              # Base classes/interfaces
│   │   └── geometry.hpp
│   └── algorithms/        # Algorithm APIs
│   │   ├── convex_hull.hpp
│   │   ├── sweep_line.hpp
│   │   ├── monotone_partition.hpp
│   │   └── triangulate_monotone.hpp
|   │
│   └── visulization/        # Visulization APIs
│    
├── src/
│   ├── core/              # Implementation details
│   │   └── geometry.cpp
│   └── algorithms/
│   │   ├── convex_hull.cpp
│   │   ├── sweep_line.cpp
│   │   ├── monotone_partition.cpp
│   │   └── triangulate_monotone.cpp
|   └── visulization/  
└── examples/
|   ├── convex_hull_demo.cpp
│   ├── sweep_line_demo.cpp
│   └── polygon_triangulation_demo.cpp
```
