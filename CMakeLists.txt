cmake_minimum_required(VERSION 3.10)

# Set project name and language
project(Raytracer LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${CMAKE_SOURCE_DIR}/include)

# Add the executable from the src directory
add_executable(app src/main.cc)
