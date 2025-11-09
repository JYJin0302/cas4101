cmake_minimum_required(VERSION 3.10)
project(MyGurobiProject)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the directory containing FindGUROBI.cmake to the module path
list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR})

# Find GUROBI
find_package(GUROBI REQUIRED)

# Include Gurobi headers
include_directories(${GUROBI_INCLUDE_DIR})

# Add your executable
add_executable(myapp main.cpp)

# Link Gurobi libraries
# Important: Link both C++ and C libraries, in this order
target_link_libraries(myapp ${GUROBI_CXX_LIBRARY} ${GUROBI_LIBRARY})
