cmake_minimum_required(VERSION 3.10)

project(MarketMaker)

# Set C++ standard (adjust as needed)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Export compile commands for tools like clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Recursively find all .cpp files in the src directory
file(GLOB_RECURSE SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

# Add the executable
add_executable(MarketMaker ${SOURCES})

# Include the src directory for headers (handles nested folders)
target_include_directories(MarketMaker PRIVATE src)