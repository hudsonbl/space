cmake_minimum_required(VERSION 3.14)

# Source files
set(SOURCE_FILES
    simulation.cpp
    mining_truck.cpp
    mining_unload_station.cpp
    home_base.cpp
    unload_station_metrics.cpp
    mining_truck_metrics.cpp
)

# Create a library target
add_library(mining_lib ${SOURCE_FILES})

# Compiler flags
target_compile_features(mining_lib PRIVATE cxx_std_23)
target_compile_options(mining_lib PRIVATE -Wall -Wextra -O2)