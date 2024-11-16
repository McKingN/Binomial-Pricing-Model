cmake_minimum_required(VERSION 3.15)

# Project name and language
project(Binomial-Pricing-Model LANGUAGES CXX)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Source files
file(GLOB SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)
# set(SOURCES
#     src/BinomialTree.cpp
#     src/BinomialTreeVertex.cpp
# )

# Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link Graphviz
# Manually specify Graphviz paths
include_directories("C:/Program Files/Graphviz/include/graphviz")
link_directories("C:/Program Files/Graphviz/lib")

# Link Graphviz library
find_library(GRAPHVIZ_LIB NAMES gvc graph PATHS "C:/Program Files/Graphviz/lib")

# Add the Graphviz library to your target
target_link_libraries(${PROJECT_NAME} PRIVATE ${GRAPHVIZ_LIB})

set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/build_temp")