cmake_minimum_required(VERSION 3.14)
project(MiningSimulation)

# Add subdirectory for source files
add_subdirectory(src)

enable_testing()

# Add the cmake folder to the module path
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

# Include Catch2 and make it available BEFORE adding the test subdirectory
include(cmake/AddCatch2.cmake)

add_executable(main main.cpp)

target_link_libraries(main PRIVATE mining_lib)

target_compile_features(main PRIVATE cxx_std_23)
target_compile_options(main PRIVATE -Wall -Wextra -O2)

# Add subdirectory for tests
add_subdirectory(tests)